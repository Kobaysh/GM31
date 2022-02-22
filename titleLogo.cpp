#include "main.h"
#include "renderer.h"
#include "titleLogo.h"


void TitleLogo::Init()
{
	// 漢字部分
	float offsetX,offsetY, sx, sy;
	sx = 670.0f /** 0.5f*/;
	sy = 256.0f /** 0.5f*/;
	offsetX = (SCREEN_WIDTH  - sx)* 0.5f;
	offsetY = (SCREEN_HEIGHT - sy)* 0.5f;

	VERTEX_3DX vertexx[4];
	vertexx[0].Position	= XMFLOAT3(offsetX, offsetY, 0.0f);
	vertexx[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		  
	vertexx[1].Position = XMFLOAT3(offsetX + sx, offsetY, 0.0f);
	vertexx[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		  
	vertexx[2].Position = XMFLOAT3(offsetX, offsetY + sy, 0.0f);
	vertexx[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		  
	vertexx[3].Position = XMFLOAT3(offsetX + sx, offsetY + sy, 0.0f);
	vertexx[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;
	sd.pSysMem = vertexx;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset\\texture\\yamiookami.png",
		NULL,
		NULL,
		&m_texture,
		NULL
		);
	assert(m_texture);
	

	// 英語部分

	sx = 1024.0f * 0.5f;
	sy = 256.0f * 0.5f;
	offsetX = (SCREEN_WIDTH  - sx)* 0.5f;
	offsetY = (SCREEN_HEIGHT - sy)* 0.5f;

	vertexx[0].Position	= XMFLOAT3(offsetX, offsetY, 0.0f);
	vertexx[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertexx[1].Position = XMFLOAT3(offsetX + sx, offsetY, 0.0f);
	vertexx[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertexx[2].Position = XMFLOAT3(offsetX, offsetY + sy, 0.0f);
	vertexx[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertexx[3].Position = XMFLOAT3(offsetX + sx, offsetY + sy, 0.0f);
	vertexx[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;

	sd.pSysMem = vertexx;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer2);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset\\texture\\darkirouls.png",
		NULL,
		NULL,
		&m_texture2,
		NULL
	);
	assert(m_texture2);



	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/unlitTexturePS.cso");


}

void TitleLogo::Uninit()
{
	m_VertexBuffer->Release();
	m_texture->Release();
	m_VertexBuffer2->Release();
	m_texture2->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TitleLogo::Update()
{
}

void TitleLogo::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, nullptr, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, nullptr, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);
	
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer2, &stride, &offset);

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture2);
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
