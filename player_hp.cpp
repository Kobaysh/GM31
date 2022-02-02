#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "camera.h"
#include "texture.h"
#include "player_hp.h"

#define FILENAME ("asset\\texture\\fade.png")

void HpPlayer::Init()
{
	Texture::Load(FILENAME);

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

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/unlitTexturePS.cso");
}

void HpPlayer::Init(XMFLOAT3 pos, XMFLOAT3 scale, int nowHP, int maxHP)
{
	m_position = pos;
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = scale;
	SetHP(nowHP, maxHP);
}

void HpPlayer::Uninit()
{
	m_vertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void HpPlayer::Draw()
{
	// 最大HPと現在のHPから割合を取得
	float per = (float)m_nowHP / m_maxHP;
	//	if (m_nowHP == m_maxHP) return;

	XMFLOAT4 color = XMFLOAT4(0, 0, 0, 0.8f);

	// 外枠表示
	Draw_OutLine(color);

	color = XMFLOAT4(0, 0, 0, 0.8f);
	// 黒い部分の表示
	Draw_Bar(color, 1.0f);

	// HP表示
	color = XMFLOAT4(1.0f, 0.5f, 0, 1.0f);
	Draw_Bar(color, per);

}

void HpPlayer::Draw_Bar(XMFLOAT4 color, float perHP)
{
	// 頂点データを書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	{
		VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;

		vertex[0].Position = XMFLOAT3(m_position.x, m_position.y, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = color;
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(m_position.x + (1.0f - (1.0f - 1.0f * perHP) )* 2 * m_scale.x, m_position.y, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = color;
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(m_position.x , m_position.y -1.0f* m_scale.y, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = color;
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(m_position.x + (1.0f - (1.0f - 1.0f * perHP)) * 2 * m_scale.x, m_position.y -1.0f* m_scale.y, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = color;
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	}
	Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定

	Renderer::SetWorldViewProjection2D();



	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(FILENAME));

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);

	if (perHP < 1.0f)
	{
		Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		{
			VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;

			float posX = m_position.x + (1.0f - (1.0f - 1.0f * perHP)) * 2 * m_scale.x;
			float amountX = 0.5f;
			float amountY = 1.5f;

			vertex[0].Position = XMFLOAT3(posX - amountX , m_position.y + amountY, 0.0f);
			vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

			vertex[1].Position = XMFLOAT3(posX + amountX, m_position.y + amountY, 0.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

			vertex[2].Position = XMFLOAT3(posX - amountX, m_position.y -1.0f* m_scale.y - amountY, 0.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

			vertex[3].Position = XMFLOAT3(posX + amountX, m_position.y -1.0f* m_scale.y - amountY, 0.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		}
		Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

		// ポリゴン描画
		Renderer::GetpDeviceContext()->Draw(4, 0);
	}
}

void HpPlayer::Draw_OutLine(XMFLOAT4 color)
{
	// 頂点データを書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	{
		VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;

		vertex[0].Position = XMFLOAT3(m_position.x - 2.0f, m_position.y + 2.0f, 0.0f);
		vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[0].Diffuse = color;
		vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

		vertex[1].Position = XMFLOAT3(m_position.x + (1.0f * 2)* m_scale.x + 2.0f, m_position.y + 2.0f, 0.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[1].Diffuse = color;
		vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

		vertex[2].Position = XMFLOAT3(m_position.x - 2.0f, m_position.y -1.0f* m_scale.y - 2.0f, 0.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[2].Diffuse = color;
		vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

		vertex[3].Position = XMFLOAT3(m_position.x + (1.0f * 2) * m_scale.x + 2.0f, m_position.y -1.0f* m_scale.y - 2.0f, 0.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
		vertex[3].Diffuse = color;
		vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	}
	Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定

	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// テクスチャ設定
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(FILENAME));

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);


	// 外枠白線
	{
		float posX = m_position.x - 1.0f;
		float amountX = 1.0f;
		float amountY = 3.5f;
		Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		{
			VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;



			vertex[0].Position = XMFLOAT3(posX - amountX , m_position.y + amountY, 0.0f);
			vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

			vertex[1].Position = XMFLOAT3(posX + amountX, m_position.y + amountY, 0.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

			vertex[2].Position = XMFLOAT3(posX - amountX, m_position.y -1.0f* m_scale.y - amountY, 0.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

			vertex[3].Position = XMFLOAT3(posX + amountX, m_position.y -1.0f* m_scale.y - amountY, 0.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		}
		Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

		// ポリゴン描画
		Renderer::GetpDeviceContext()->Draw(4, 0);
	

	
		Renderer::GetpDeviceContext()->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		{
			VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;

			posX = m_position.x + 2 * m_scale.x + 1.0f;

			vertex[0].Position = XMFLOAT3(posX - amountX , m_position.y + amountY, 0.0f);
			vertex[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

			vertex[1].Position = XMFLOAT3(posX + amountX, m_position.y + amountY, 0.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

			vertex[2].Position = XMFLOAT3(posX - amountX, m_position.y -1.0f* m_scale.y - amountY, 0.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

			vertex[3].Position = XMFLOAT3(posX + amountX, m_position.y -1.0f* m_scale.y - amountY, 0.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
		}
		Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

		// ポリゴン描画
		Renderer::GetpDeviceContext()->Draw(4, 0);
	}

}
