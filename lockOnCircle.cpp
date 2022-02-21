#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "lockOnCircle.h"

const std::string LockOnCircle::TEXTURE_FILE_NAME = "asset\\texture\\circle.png";

void LockOnCircle::Init()
{
	Texture::Load(TEXTURE_FILE_NAME);

	m_position = m_object->GetPosition();
	m_scale = XMFLOAT3(1.5f, 1.5f, 1.0f);

	VERTEX_3DX vertex[4];
	vertex[0].Position	= XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(+0.5f, 0.5f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;	// 頂点バッファを動的変更可能に
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4; // バイト幅
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
											//	bd.CPUAccessFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);


	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_pixelShader, "asset/shader/unlitTexturePS.cso");

}

void LockOnCircle::Uninit()
{
	m_vertexBuffer->Release();
	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
}

void LockOnCircle::Update()
{
	m_position = m_object->GetPosition();
}

void LockOnCircle::Draw()
{
	// 頂点データを書き換え
	//D3D11_MAPPED_SUBRESOURCE msr;
	//Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//{
	//	VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;
	//	float offsetY = m_scale.y;
	//	float posX = SCREEN_WIDTH * 0.5f;
	//	float posY = SCREEN_HEIGHT * 0.5f;

	//	//vertex[0].Position	= XMFLOAT3(m_position.x -0.5f * m_scale.x,m_position.y + 0.5f* m_scale.y - offsetY, 0.0f);
	//	//vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//	//vertex[1].Position = XMFLOAT3(m_position.x +0.5f* m_scale.x,m_position.y  + 0.5f* m_scale.y- offsetY, 0.0f);
	//	//vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//	//vertex[2].Position = XMFLOAT3(m_position.x -0.5f* m_scale.x,m_position.y  -0.5f* m_scale.y- offsetY, 0.0f);
	//	//vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//	//vertex[3].Position = XMFLOAT3(m_position.x + 0.5f* m_scale.x,m_position.y  -0.5f* m_scale.y- offsetY, 0.0f);
	//	//vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//	vertex[0].Position	= XMFLOAT3(posX -0.5f * m_scale.x,posY + 0.5f* m_scale.y - offsetY, 0.0f);
	//	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//	vertex[1].Position = XMFLOAT3(posX +0.5f* m_scale.x,posY  + 0.5f* m_scale.y- offsetY, 0.0f);
	//	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//	vertex[2].Position = XMFLOAT3(posX -0.5f* m_scale.x,posY  -0.5f* m_scale.y- offsetY, 0.0f);
	//	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//	vertex[3].Position = XMFLOAT3(posX + 0.5f* m_scale.x,posY  -0.5f* m_scale.y- offsetY, 0.0f);
	//	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	//}
	//Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);
	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
//	Renderer::SetWorldMatrixX(&world4x4);

	Renderer::SetWorldViewProjection2D(&world4x4);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(TEXTURE_FILE_NAME));

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
