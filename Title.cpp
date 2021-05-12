#include "main.h"
#include "Title.h"
#include "Renderer.h"

void Title::Init()
{
	VERTEX_3DX vertexx[4];
	vertexx[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertexx[1].Position = XMFLOAT3(200.0f, 0.0f, 0.0f);
	vertexx[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertexx[2].Position = XMFLOAT3(0.0f, 200.0f, 0.0f);
	vertexx[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertexx[3].Position = XMFLOAT3(200.0f, 200.0f, 0.0f);
	vertexx[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
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

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Vertexbuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetDevice(),
		"asset/texture/grass02.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}

void Title::Uninit()
{
	m_Vertexbuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Title::Update()
{
}

void Title::Draw()
{
}
