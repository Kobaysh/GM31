#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "texture.h"

#define FILENAME ("asset\\texture\\fade.png")

// 静的変数
float Fade::m_FadeAlpha;			// フェードα値
Fade::FadeType Fade::m_FadeType;	// フェードタイプ

static 	VERTEX_3DX vertex[4];		// 頂点
static D3D11_BUFFER_DESC bd{};		// 頂点バッファデスク
static D3D11_SUBRESOURCE_DATA sd{};	// サブリソースデータ
void Fade::Init()
{


	vertex[0].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		  
	vertex[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		  
	vertex[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		  
	vertex[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成


	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;


	sd.pSysMem = vertex;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	Texture::Load(FILENAME);

	// シェーダー作成
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/unlitTexturePS.cso");

	m_FadeAlpha = 0.0f;
	m_FadeType = FadeType::FADE_NONE;

}

void Fade::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Fade::Update()
{
	switch (m_FadeType)
	{
	case Fade::FADE_NONE:
		break;
	case Fade::FADE_IN:
		m_FadeAlpha -= 0.01f;

		vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
		break;
	case Fade::FADE_OUT:
		m_FadeAlpha += 0.01f;

		vertex[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, m_FadeAlpha);
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
		break;
	case Fade::FADE_MAX:
		break;
	default:
		break;
	}

	if (m_FadeAlpha >= 1.05f || m_FadeAlpha <= -0.05f) {
		m_FadeType = FadeType::FADE_NONE;
	}

}

void Fade::Draw()
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
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(FILENAME));

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);
	

}

void Fade::SetFade(FadeType type)
{
	m_FadeType = type;

	switch (m_FadeType)
	{
	case Fade::FADE_NONE:
		break;
	case Fade::FADE_IN:
		m_FadeAlpha = 1.0f;
		break;
	case Fade::FADE_OUT:
		m_FadeAlpha = 0.0f;
		break;
	case Fade::FADE_MAX:
		break;
	default:
		break;
	}
}

Fade::FadeType Fade::GetFadeType()
{
	return m_FadeType;
}
