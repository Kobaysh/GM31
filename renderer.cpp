
#include "main.h"
#include "renderer.h"
#include <io.h>

D3D_FEATURE_LEVEL       Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           Renderer::m_Device = nullptr;
ID3D11DeviceContext*    Renderer::m_DeviceContext = nullptr;
//IDXGISwapChain*         Renderer::m_SwapChain = NULL;
//ID3D11RenderTargetView* Renderer::m_RenderTargetView = NULL;
//ID3D11DepthStencilView* Renderer::m_DepthStencilView = NULL;

ComPtr<ID3D11Device>			Renderer::m_pDevice = nullptr;
ComPtr<ID3D11DeviceContext>		Renderer::m_pDeviceContext = nullptr;
ComPtr<IDXGISwapChain>			Renderer::m_pSwapChain = nullptr;
ComPtr<ID3D11RenderTargetView>	Renderer::m_pRenderTargetView = nullptr;
ComPtr<ID3D11DepthStencilView>	Renderer::m_pDepthStencilView = nullptr;

//ID3D11Buffer*			Renderer::m_WorldBuffer = NULL;
//ID3D11Buffer*			Renderer::m_ViewBuffer = NULL;
//ID3D11Buffer*			Renderer::m_ProjectionBuffer = NULL;
//ID3D11Buffer*			Renderer::m_MaterialBuffer = NULL;
//ID3D11Buffer*			Renderer::m_LightBuffer = NULL;

 ComPtr<ID3D11Buffer>	Renderer::m_pWorldBuffer = nullptr;
 ComPtr<ID3D11Buffer>	Renderer::m_pViewBuffer = nullptr;
 ComPtr<ID3D11Buffer>	Renderer::m_pProjectionBuffer = nullptr;
 ComPtr<ID3D11Buffer>	Renderer::m_pMaterialBuffer = nullptr;
 ComPtr<ID3D11Buffer>	Renderer::m_pLightBuffer = nullptr;
 ComPtr<ID3D11Buffer>	Renderer::m_pCameraBuffer = nullptr;
 ComPtr<ID3D11Buffer>	Renderer::m_pParameterBuffer = nullptr;


ID3D11DepthStencilState* Renderer::m_DepthStateEnable = nullptr;
ID3D11DepthStencilState* Renderer::m_DepthStateDisable = nullptr;

ComPtr<ID3D11RasterizerState> Renderer::m_pRS_FillSolid = nullptr;
ComPtr<ID3D11RasterizerState> Renderer::m_pRS_FillWireFrame = nullptr;




void Renderer::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = true;
	rd.MultisampleEnable = true;
	
	GetpDevice()->CreateRasterizerState(&rd, m_pRS_FillWireFrame.GetAddressOf());

	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_BACK;
	rd.FrontCounterClockwise = true;
	rd.MultisampleEnable = false;

	GetpDevice()->CreateRasterizerState(&rd, m_pRS_FillSolid.GetAddressOf());

}

void Renderer::Init()
{
	HRESULT hr = S_OK;




	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = GetWindow();
//	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Count = 16;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	/*hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&swapChainDesc,
										&m_SwapChain,
										&m_Device,
										&m_FeatureLevel,
										&m_DeviceContext );*/
	hr = D3D11CreateDeviceAndSwapChain( nullptr,
										D3D_DRIVER_TYPE_HARDWARE,
										nullptr,
										0,
										nullptr,
										0,
										D3D11_SDK_VERSION,
										&swapChainDesc,
										&m_pSwapChain,
										&m_pDevice,
										&m_FeatureLevel,
										&m_pDeviceContext );
	





	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget = nullptr;
	/*m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&renderTarget );
	m_Device->CreateRenderTargetView( renderTarget, NULL, &m_RenderTargetView );
	*/
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	m_pDevice->CreateRenderTargetView(renderTarget, nullptr, &m_pRenderTargetView);

	renderTarget->Release();


	// デプスステンシルバッファ作成
	ID3D11Texture2D* depthStencile = nullptr;
	D3D11_TEXTURE2D_DESC textureDesc{};
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	//m_Device->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	m_pDevice->CreateTexture2D(&textureDesc, nullptr, &depthStencile);

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
//	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	//m_Device->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_DepthStencilView);
	m_pDevice->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, &m_pDepthStencilView);
	depthStencile->Release();


	//m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
	m_pDeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());





	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)SCREEN_WIDTH;
	viewport.Height = (FLOAT)SCREEN_HEIGHT;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	//m_DeviceContext->RSSetViewports( 1, &viewport );
	m_pDeviceContext->RSSetViewports( 1, &viewport );



	// ラスタライザステート設定
	CreateRasterizerState();

	m_pDeviceContext->RSSetState(m_pRS_FillSolid.Get());




	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc{};
//	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.AlphaToCoverageEnable = TRUE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	ID3D11BlendState* blendState = nullptr;
	/*m_Device->CreateBlendState( &blendDesc, &blendState );
	m_DeviceContext->OMSetBlendState( blendState, blendFactor, 0xffffffff );*/
	m_pDevice->CreateBlendState(&blendDesc, &blendState);
	m_pDeviceContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);



	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	//m_Device->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateEnable );//深度有効ステート
	m_pDevice->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateEnable );//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	//m_Device->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateDisable );//深度無効ステート
	m_pDevice->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateDisable );//深度無効ステート

	//m_DeviceContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );
	m_pDeviceContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
//	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
	samplerDesc.MaxAnisotropy = 16;

	ID3D11SamplerState* samplerState = nullptr;
//	m_Device->CreateSamplerState( &samplerDesc, &samplerState );
	m_pDevice->CreateSamplerState( &samplerDesc, &samplerState );

//	m_DeviceContext->PSSetSamplers( 0, 1, &samplerState );
	m_pDeviceContext->PSSetSamplers( 0, 1, &samplerState );



	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
//	bufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	bufferDesc.ByteWidth = sizeof(XMFLOAT4X4);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	/*m_Device->CreateBuffer( &bufferDesc, NULL, &m_WorldBuffer );
	m_DeviceContext->VSSetConstantBuffers( 0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer( &bufferDesc, NULL, &m_ViewBuffer );
	m_DeviceContext->VSSetConstantBuffers( 1, 1, &m_ViewBuffer );

	m_Device->CreateBuffer( &bufferDesc, NULL, &m_ProjectionBuffer );
	m_DeviceContext->VSSetConstantBuffers( 2, 1, &m_ProjectionBuffer );


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer( &bufferDesc, NULL, &m_MaterialBuffer );
	m_DeviceContext->VSSetConstantBuffers( 3, 1, &m_MaterialBuffer );


	bufferDesc.ByteWidth = sizeof(LIGHT);

	m_Device->CreateBuffer( &bufferDesc, nullptr, &m_LightBuffer );
	m_DeviceContext->VSSetConstantBuffers( 4, 1, &m_LightBuffer );
	m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);*/
	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pWorldBuffer);
	m_pDeviceContext->VSSetConstantBuffers(0, 1, m_pWorldBuffer.GetAddressOf());

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pViewBuffer);
	m_pDeviceContext->VSSetConstantBuffers(1, 1, m_pViewBuffer.GetAddressOf());

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pProjectionBuffer);
	m_pDeviceContext->VSSetConstantBuffers(2, 1, m_pProjectionBuffer.GetAddressOf());


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pMaterialBuffer);
	m_pDeviceContext->VSSetConstantBuffers(3, 1, m_pMaterialBuffer.GetAddressOf());


//	bufferDesc.ByteWidth = sizeof(LIGHT);
	bufferDesc.ByteWidth = sizeof(LIGHTX);

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pLightBuffer);
	m_pDeviceContext->VSSetConstantBuffers(4, 1, m_pLightBuffer.GetAddressOf());
	m_pDeviceContext->PSSetConstantBuffers(4, 1, m_pLightBuffer.GetAddressOf());


	bufferDesc.ByteWidth = sizeof(XMFLOAT4);
	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pCameraBuffer);
	m_pDeviceContext->VSSetConstantBuffers(5, 1, m_pCameraBuffer.GetAddressOf());
	m_pDeviceContext->PSSetConstantBuffers(5, 1, m_pCameraBuffer.GetAddressOf());

	m_pDevice->CreateBuffer(&bufferDesc, nullptr, &m_pParameterBuffer);
	m_pDeviceContext->VSSetConstantBuffers(6, 1, m_pParameterBuffer.GetAddressOf());
	m_pDeviceContext->PSSetConstantBuffers(6, 1, m_pParameterBuffer.GetAddressOf());



	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	SetLight(light);

	LIGHTX lightx{};
	lightx.Enable = true;
	XMVECTOR vector = XMVectorSet(1.0f, -1.0f, 1.0f, 0.0f);
	vector =  XMVector3Normalize(vector);
	XMStoreFloat4(&lightx.Direction, vector);
	lightx.Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	lightx.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetLightX(lightx);


	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);




}



void Renderer::Uninit()
{

	/*m_WorldBuffer->Release();
	m_ViewBuffer->Release();
	m_ProjectionBuffer->Release();
	m_LightBuffer->Release();
	m_MaterialBuffer->Release();*/

	m_pWorldBuffer->Release();
	m_pViewBuffer->Release();
	m_pProjectionBuffer->Release();
	m_pLightBuffer->Release();
	m_pMaterialBuffer->Release();


	/*m_DeviceContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_DeviceContext->Release();
	m_Device->Release();*/
	m_pDeviceContext->ClearState();
	m_pRenderTargetView->Release();
	m_pSwapChain->Release();
	m_pDeviceContext->Release();
	m_pDevice->Release();

}




void Renderer::Begin()
{
	float clearColor[4] = { 0.8f, 0.8f, 0.2f, 1.0f };
	
	/*m_DeviceContext->ClearRenderTargetView( m_RenderTargetView, clearColor );
	m_DeviceContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);*/
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView.Get(), clearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}



void Renderer::End()
{
	//m_SwapChain->Present( 1, 0 );
	m_pSwapChain->Present( 1, 0 );
}




void Renderer::SetDepthEnable( bool Enable )
{
	/*if( Enable )
		m_DeviceContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );
	else
		m_DeviceContext->OMSetDepthStencilState( m_DepthStateDisable, NULL );
*/
	if (Enable)
		m_pDeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		m_pDeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);
}

void Renderer::SetWorldViewProjection2D()
{
	//D3DXMATRIX world;
	//D3DXMatrixIdentity(&world);
	//D3DXMatrixTranspose(&world, &world);

	//m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	//D3DXMATRIX view;
	//D3DXMatrixIdentity(&view);
	//D3DXMatrixTranspose(&view, &view);
	//m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	//D3DXMATRIX projection;
	//D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
	//D3DXMatrixTranspose(&projection, &projection);
	//m_DeviceContext->UpdateSubresource( m_ProjectionBuffer, 0, NULL, &projection, 0, 0 );
	XMMATRIX world;
    world =	XMMatrixIdentity();
	world = XMMatrixTranspose(world);

	m_pDeviceContext->UpdateSubresource(m_pWorldBuffer.Get(), 0, nullptr, &world, 0, 0);

	XMMATRIX view;
	view = XMMatrixIdentity();
	view = XMMatrixTranspose(view);
	m_pDeviceContext->UpdateSubresource(m_pViewBuffer.Get(), 0, nullptr, &view, 0, 0);

	XMMATRIX projection;
	projection = XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
 	projection = XMMatrixTranspose(projection);
	m_pDeviceContext->UpdateSubresource(m_pProjectionBuffer.Get(), 0, nullptr, &projection, 0, 0);
}


void Renderer::SetWorldMatrix( D3DXMATRIX* WorldMatrix )
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	m_DeviceContext->UpdateSubresource(m_pWorldBuffer.Get(), 0, nullptr, &world, 0, 0);
}

void Renderer::SetViewMatrix( D3DXMATRIX* ViewMatrix )
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	m_DeviceContext->UpdateSubresource(m_pViewBuffer.Get(), 0, nullptr, &view, 0, 0);
}

void Renderer::SetProjectionMatrix( D3DXMATRIX* ProjectionMatrix )
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	//m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
	m_pDeviceContext->UpdateSubresource(m_pProjectionBuffer.Get(), 0, nullptr, &projection, 0, 0);
}

void Renderer::SetWorldMatrixX(XMFLOAT4X4 * WorldMatrix)
{
	XMMATRIX world = XMMatrixTranspose(XMLoadFloat4x4( WorldMatrix));
	//m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
	m_pDeviceContext->UpdateSubresource(m_pWorldBuffer.Get(), 0, nullptr, &world, 0, 0);
}

void Renderer::SetViewMatrixX(XMFLOAT4X4 * ViewMatrix)
{
	XMMATRIX view= XMMatrixTranspose(XMLoadFloat4x4(ViewMatrix));
	//m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
	m_pDeviceContext->UpdateSubresource(m_pViewBuffer.Get(), 0, nullptr, &view, 0, 0);
}

void Renderer::SetProjectionMatrixX(XMFLOAT4X4 * ProjectionMatrix)
{
	XMMATRIX projection = XMMatrixTranspose(XMLoadFloat4x4(ProjectionMatrix));
	//m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
	m_pDeviceContext->UpdateSubresource(m_pProjectionBuffer.Get(), 0, nullptr, &projection, 0, 0);
}



void Renderer::SetMaterial( MATERIAL Material )
{
//	m_DeviceContext->UpdateSubresource( m_MaterialBuffer, 0, NULL, &Material, 0, 0 );
	m_pDeviceContext->UpdateSubresource( m_pMaterialBuffer.Get(), 0, nullptr, &Material, 0, 0 );
}

void Renderer::SetMaterialX(MATERIALX Material)
{
	m_pDeviceContext->UpdateSubresource(m_pMaterialBuffer.Get(), 0, nullptr, &Material, 0, 0);

}

void Renderer::SetLight( LIGHT Light )
{
//	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);
	m_pDeviceContext->UpdateSubresource(m_pLightBuffer.Get(), 0, nullptr, &Light, 0, 0);
}

void Renderer::SetLightX(LIGHTX Light)
{
	m_pDeviceContext->UpdateSubresource(m_pLightBuffer.Get(), 0, nullptr, &Light, 0, 0);
}

void Renderer::SetCameraPosition(XMFLOAT3 cameraPos)
{
	m_pDeviceContext->UpdateSubresource(m_pCameraBuffer.Get(), 0, nullptr, &XMFLOAT4(cameraPos.x, cameraPos.y, cameraPos.z, 1.0f), 0, 0);
}

void Renderer::SetParameter(XMFLOAT4 parameter)
{
	m_pDeviceContext->UpdateSubresource(m_pParameterBuffer.Get(), 0, nullptr, &parameter, 0, 0);
}





void Renderer::CreateVertexShader( ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName )
{

	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

//	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);
	m_pDevice->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 4 * 3, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 4 * 6, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

//	m_Device->CreateInputLayout(layout,
	m_pDevice->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}



void Renderer::CreatePixelShader( ID3D11PixelShader** PixelShader, const char* FileName )
{
	FILE* file;
	long int fsize;

	file = fopen(FileName, "rb");
	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

//	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);
	m_pDevice->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;
}


