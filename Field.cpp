#include "main.h"
#include "renderer.h"
#include "field.h"

void Field::Init()
{
	VERTEX_3DX vertexx[4];
	vertexx[0].Position = XMFLOAT3(-100.0f, 0.0f, 100.0f);
	vertexx[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexx[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertexx[1].Position = XMFLOAT3(100.0f, 0.0f, 100.0f);
	vertexx[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexx[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[1].TexCoord = XMFLOAT2(100.0f, 0.0f);

	vertexx[2].Position = XMFLOAT3(-100.0f,0.0f, -100.0f);
	vertexx[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexx[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 100.0f);

	vertexx[3].Position = XMFLOAT3(100.0f, 0.0f, -100.0f);
	vertexx[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexx[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[3].TexCoord = XMFLOAT2(100.0f, 100.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// バイト幅
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;
	sd.pSysMem = vertexx;

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);
	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		//Renderer::GetDevice(),
		Renderer::GetpDevice().Get(),
		"asset/texture/grass02.jpg",
		NULL,
		NULL,
		&m_texture,
		NULL
	);
	assert(m_texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
//	Renderer::GetpDeviceContext()->GenerateMips(m_texture);
	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void Field::Uninit()
{
	m_vertexBuffer->Release();
	m_texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Field::Update()
{

}

void Field::Draw()
{
	// 入力レイアウト設定
	//Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//// シェーダー設定
	//Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	//Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	/*D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_rotation.y, m_rotation.x, m_rotation.z);
	D3DXMatrixTranslation(&trans, m_position.x, m_position.y, m_position.z);
	world = scale * rot*trans;
	Renderer::SetWorldMatrix(&world);*/

	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x,m_rotation.y,m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	
	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	Renderer::SetMaterial(material);
	

	// テクスチャ設定
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture);
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// プリミティブトポロジ設定
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	//Renderer::GetDeviceContext()->Draw(4, 0);
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
