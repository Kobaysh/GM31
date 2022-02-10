#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "texture.h"
#include "hp.h"

#define FILENAME ("asset\\texture\\fade.png")

void HpBar::Init()
{
	Texture::Load(FILENAME);
	if (!m_vertexBuffer)
	{
		VERTEX_3DX vertexx[4];
		vertexx[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertexx[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertexx[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertexx[1].Position = XMFLOAT3(1.0f, 1.0f, 0.0f);
		vertexx[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertexx[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertexx[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertexx[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertexx[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertexx[3].Position = XMFLOAT3(1.0f, -1.0f, 0.0f);
		vertexx[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertexx[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


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
		sd.pSysMem = vertexx;

		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);
	}
	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, "asset/shader/unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_pixelShader, "asset/shader/unlitTexturePS.cso");
}

void HpBar::Init(XMFLOAT3 pos, XMFLOAT3 scale, int nowHP, int maxHP)
{
	m_position = pos;
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = scale;
	SetHP(nowHP, maxHP);
}

void HpBar::Uninit()
{
	m_vertexBuffer->Release();
	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
}

void HpBar::Draw()
{
	// 視錘台カリング
	Scene* scene = ManagerT::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(GOT_CAMERA);
	if (!camera->CheckView(m_position))
	{
		return;
	}
	// 最大HPと現在のHPから割合を取得
	float per = (float)m_nowHP / m_maxHP;
//	if (m_nowHP == m_maxHP) return;

	XMFLOAT4 color = XMFLOAT4(0, 0, 0, 1.0f);


	// 黒い部分の表示
	Draw_Bar(color, 1.0f);

	// ３０％以下で赤色表示
	if (per > 0.0f && per <= 0.3f)
	{
		color = XMFLOAT4(1.0f, 0, 0, 1.0f);
	}
	// ６０％以下で黄色表示
	else if (per > 0.3f && per <= 0.6f)
	{
		color = XMFLOAT4(1.0f, 1.0f, 0, 1.0f);
	}
	// １００％以下で緑色表示
	else if (per > 0.6f && per <= 1.0f)
	{
		color = XMFLOAT4(0, 1.0f, 0, 1.0f);
	}

	if (per == 1.0f) {
		Draw_Bar(color, 1.0f);
	}
	else {
		Draw_Bar(color, per);
	}
}

void HpBar::Draw_Bar(XMFLOAT4 color, float perHP)
{
	// 頂点データを書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	{
		VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;

		vertex[0].Position = XMFLOAT3(-1.0f, 1.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = color;
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(1.0f - (1.0f - 1.0f * perHP) * 2, 1.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = color;
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(-1.0f, -1.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = color;
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(1.0f - (1.0f - 1.0f * perHP) * 2, -1.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = color;
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	}
	Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// マトリクス設定

	Scene* scene = ManagerT::GetScene();
	XMMATRIX mtxInvView;
	XMMATRIX view =XMLoadFloat4x4(scene->GetGameObject<Camera>(GOT_CAMERA)->GetView());
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, view);
	temp._41 = 0.0f;
	temp._42 = 0.0f;
	temp._43 = 0.0f;
	view =	XMLoadFloat4x4(&temp);

	mtxInvView = XMMatrixTranspose(view);
	//	mtxInvView = XMMatrixInverse(nullptr, view);

	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * mtxInvView * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);


	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	Renderer::SetMaterial(material);


	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(FILENAME));
	//Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
