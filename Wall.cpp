#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "wall.h"
#include "animationModel.h"
#include "model.h"
#include "obb.h"


#define FILENAME ("asset\\model\\wall\\wall_mapping.obj")

void Wall::Init()
{
	//VERTEX_3DX vertexx[4];
	//vertexx[0].Position = XMFLOAT3(-10.0f, 0.0f, 10.0f);
	//vertexx[0].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//vertexx[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//vertexx[1].Position = XMFLOAT3(10.0f, 0.0f, 10.0f);
	//vertexx[1].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//vertexx[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//vertexx[2].Position = XMFLOAT3(-10.0f, 0.0f, -10.0f);
	//vertexx[2].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertexx[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//vertexx[3].Position = XMFLOAT3(10.0f, 0.0f, -10.0f);
	//vertexx[3].Normal = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//vertexx[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	//// 頂点バッファ生成
	//D3D11_BUFFER_DESC bd{};

	//bd.Usage = D3D11_USAGE_DEFAULT;
	////	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// バイト幅
	//bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// バッファの種類
	//bd.CPUAccessFlags = 0;

	//D3D11_SUBRESOURCE_DATA sd{};
	////sd.pSysMem = vertex;
	//sd.pSysMem = vertexx;

	////Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);
	//Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	//// テクスチャ読み込み
	//D3DX11CreateShaderResourceViewFromFile(
	//	//Renderer::GetDevice(),
	//	Renderer::GetpDevice().Get(),
	//	"asset/texture/grass02.jpg",
	//	NULL,
	//	NULL,
	//	&m_texture,
	//	NULL
	//);
	//assert(m_texture);

	m_modelId = Model::SetModelLoadfile(FILENAME);
	Model::Load(m_modelId);

	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, "asset/shader/pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_pixelShader, "asset/shader/pixelLightingPS.cso");

	m_position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	XMFLOAT3 obbScale = XMFLOAT3(m_scale.x * 2.0f, m_scale.y * 2.0f, m_scale.z * 2.0f);
	m_obb = new OBB(m_position, obbScale);
	ManagerT::GetScene()->AddGameObject<OBB>(m_obb, GameObject::GOT_OBJECT3D);
}

void Wall::Uninit()
{
//	m_vertexBuffer->Release();
//	m_texture->Release();
//	Model::Release(m_modelId);
	m_obb->SetDead();

	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
}

void Wall::Update()
{
	m_obb->SetPosition(m_position);
}

void Wall::Draw()
{
	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMFLOAT3 axisX = XMFLOAT3(1.0f, 0.0f, 0.0f);
	XMFLOAT3 axisY = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMMATRIX rotWall = XMMatrixRotationAxis(XMLoadFloat3(&axisX), XMConvertToRadians(90.0f));
	XMMATRIX worldX = scaleX * rotX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	//// 頂点バッファ設定
	//UINT stride = sizeof(VERTEX_3DX);
	//UINT offset = 0;
	//Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);


	//// マテリアル設定
	//MATERIAL material;
	//ZeroMemory(&material, sizeof(material));
	//material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	//Renderer::SetMaterial(material);


	//// テクスチャ設定
	//Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	//// プリミティブトポロジ設定
	//Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// ポリゴン描画
	//Renderer::GetpDeviceContext()->Draw(4, 0);
	//m_model->Draw();
	Model::Draw(m_modelId);
}
