#include "main.h"
#include "renderer.h"
#include "titleLogo.h"

#define FILENAME ("asset/texture/kusodekatitle.png")

void TitleLogo::Init()
{
	/*VERTEX_3D vertex[4];
	vertex[0].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= D3DXVECTOR2(0.0f, 0.0f);
	
	vertex[1].Position	= D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position	= D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position	= D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= D3DXVECTOR2(1.0f, 1.0f);*/

	VERTEX_3DX vertexx[4];
	vertexx[0].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		  
	vertexx[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertexx[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		  
	vertexx[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertexx[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		  
	vertexx[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertexx[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


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

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
	//	Renderer::GetDevice(),
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

void TitleLogo::Uninit()
{
	m_VertexBuffer->Release();
	m_texture->Release();

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
	//Renderer::GetDeviceContext()->IASetInputLayout(m_pVertexLayout);

	//// シェーダー設定
	//Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	//Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//// テクスチャ設定
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	//// プリミティブトポロジ設定
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// ポリゴン描画
	//Renderer::GetDeviceContext()->Draw(4, 0);
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);
	

}
