#include "main.h"
#include "renderer.h"
#include "explaLock.h"
#include "texture.h"
#include "input.h"


void ExplaLock::Init()
{
	VERTEX_3DX vertex[4];
	float x, y, sx, sy;
	x = SCREEN_WIDTH / 20;
	y = SCREEN_HEIGHT / 4 + 70.0f + TEXTURE_SIZE_Y + TEXTURE_SIZE_Y +TEXTURE_SIZE_Y;
	sx = TEXTURE_SIZE_X;
	sy = TEXTURE_SIZE_Y;
//	x -= sx / 2;
	vertex[0].Position	= XMFLOAT3(x, y, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(x + sx, y, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(x, y + sy, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(x + sx, y + sy, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset\\texture\\i_lock.png",
		NULL,
		NULL,
		&m_textureKey,
		NULL
	);
	assert(m_textureKey);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset\\texture\\mouse_lock.png",
		NULL,
		NULL,
		&m_textureMouse,
		NULL
	);
	assert(m_textureMouse);


	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_pixelShader, "asset/shader/unlitTexturePS.cso");
}

void ExplaLock::Uninit()
{
	m_textureKey->Release();
	m_textureMouse->Release();
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_vertexLayout->Release();
}

void ExplaLock::Update()
{
}

void ExplaLock::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// テクスチャ設定
	if (Input::GetMouseActive())
	{
		Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_textureMouse);
	}
	else
	{
		Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_textureKey);

	}
	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);

}
