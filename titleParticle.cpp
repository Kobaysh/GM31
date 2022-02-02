#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "titleParticle.h"

#define TEXTURE_NAME ("asset\\texture\\circle.png")

ID3D11InputLayout* TitleParticle::m_sVertexLayout = nullptr; 
ID3D11VertexShader* TitleParticle::m_sVertexShader = nullptr; 
ID3D11PixelShader* TitleParticle::m_sPixelShader = nullptr; 
ID3D11Buffer* TitleParticle::m_VertexBuffer = nullptr; 
ID3D11ShaderResourceView* TitleParticle::m_texture = nullptr; 

void TitleParticle::Init()
{
	if (!m_VertexBuffer)
	{
		VERTEX_3DX vertexx[4];
		vertexx[0].Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertexx[0].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertexx[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.3f);
		vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertexx[1].Position = XMFLOAT3(512.0f, 0.0f, 0.0f);
		vertexx[1].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertexx[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.3f);
		vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertexx[2].Position = XMFLOAT3(0.0f, 512.0f, 0.0f);
		vertexx[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertexx[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.3f);
		vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertexx[3].Position = XMFLOAT3(512.0f, 512.0f, 0.0f);
		vertexx[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
		vertexx[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 0.3f);
		vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


		// 頂点バッファ生成
		D3D11_BUFFER_DESC bd{};

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		sd.pSysMem = vertexx;
		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	if (!m_texture)
	{
		// テクスチャ読み込み
		D3DX11CreateShaderResourceViewFromFile(
			Renderer::GetpDevice().Get(),
			TEXTURE_NAME,
			NULL,
			NULL,
			&m_texture,
			NULL
		);
	}
	if (!m_sVertexLayout && !m_sVertexShader)
	{
		Renderer::CreateVertexShader(&m_sVertexShader, &m_sVertexLayout, "asset/shader/unlitTextureVS.cso");
	}
	if (!m_sPixelShader)
	{
		Renderer::CreatePixelShader(&m_sPixelShader, "asset/shader/unlitTexturePS.cso");
	}

	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(0.1f, 0.1f, 1.0f);
}

void TitleParticle::Uninit()
{
}

void TitleParticle::Update()
{
	XMVECTOR vPostion, vMove;
	vPostion = XMLoadFloat3(&m_position);
	vMove = { -1.0f,0.3f,0.0f,0.0f };
	vPostion += vMove;
	XMStoreFloat3(&m_position, vPostion);
	if (m_position.x + 512.0f * 0.5f * m_scale.x <= 0.0f)
	{
		this->SetDead();
	}
	else if (m_position.y - 512.0f * 0.5f * m_scale.y >= SCREEN_HEIGHT)
	{
		this->SetDead();
	}
}

void TitleParticle::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_sVertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_sVertexShader, nullptr, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_sPixelShader, nullptr, 0);

	// マトリクス設定
	XMMATRIX mtxW, mtxT, mtxS;
	mtxS = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	mtxT = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	mtxW = mtxS * mtxT;
	XMFLOAT4X4 world;
	XMStoreFloat4x4(&world, mtxW);
	Renderer::SetWorldViewProjection2D(&world);

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

void TitleParticle::Create(float offsetY)
{
	ManagerT::GetScene()->AppendGameObject<TitleParticle>(GOT_OBJECT2D)->SetPosition(XMFLOAT3(SCREEN_WIDTH, offsetY, 0.0f));
}

void TitleParticle::Unload()
{
	m_VertexBuffer->Release();
	m_VertexBuffer= nullptr;
	m_texture->Release();
	m_texture = nullptr;
}
