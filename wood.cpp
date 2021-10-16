#include "main.h"
#include "renderer.h"
#include "wood.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"

#define FILENAME ("asset/texture/wood.png")


void Wood::Init()
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
	//sd.pSysMem = vertex;
	sd.pSysMem = vertexx;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(
		//Renderer::GetDevice(),
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

	m_position = XMFLOAT3(0.0f, 3.0f, 10.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

}

void Wood::Uninit()
{
	m_vertexBuffer->Release();
	m_texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Wood::Update()
{

}

void Wood::Draw()
{

	Renderer::GetpDeviceContext()->Unmap(m_vertexBuffer, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

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
	Renderer::SetWorldMatrixX(&worldX);

	

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
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// プリミティブトポロジ設定
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
