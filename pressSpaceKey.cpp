#include "main.h"
#include "renderer.h"
#include "pressSpaceKey.h"

#define FILENAME ("asset/texture/PressSpaceKey.png")

#define OFFSET_X (240.0f)
#define OFFSET_Y (420.0f)

// 静的変数

static 	VERTEX_3DX vertex[4];
static D3D11_BUFFER_DESC bd{};
static D3D11_SUBRESOURCE_DATA sd{};
static float value = 0.0f;

void PressSpaceKey::Init()
{
	m_fadeAlpha = 1.0f;
	value = 0.0f;


	vertex[0].Position	= XMFLOAT3(0.0f + OFFSET_X, 0.0f + OFFSET_Y, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		  
	vertex[1].Position = XMFLOAT3(439.0f + OFFSET_X, 0.0f + OFFSET_Y, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		  
	vertex[2].Position = XMFLOAT3(0.0f + OFFSET_X, 87.0f + OFFSET_Y, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		  
	vertex[3].Position = XMFLOAT3(439.0f + OFFSET_X, 87.0f + OFFSET_Y, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成


	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;


	sd.pSysMem = vertex;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		FILENAME,
		NULL,
		NULL,
		&m_texture,
		NULL
		);
	assert(m_texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");


}

void PressSpaceKey::Uninit()
{
	m_VertexBuffer->Release();
	m_texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void PressSpaceKey::Update()
{

	vertex[0].Position = XMFLOAT3(0.0f + OFFSET_X, 0.0f + OFFSET_Y, 0.0f);
	vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(439.0f + OFFSET_X, 0.0f + OFFSET_Y, 0.0f);
	vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(0.0f + OFFSET_X, 87.0f + OFFSET_Y, 0.0f);
	vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(439.0f + OFFSET_X, 87.0f + OFFSET_Y, 0.0f);
	vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_fadeAlpha);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	value += 0.1f;

	m_fadeAlpha = cosf(value) * 0.5f + 0.5f;

}

void PressSpaceKey::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

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
	

}
