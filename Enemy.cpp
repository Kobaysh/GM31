#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "model.h"
#include "audio.h"
#include "obb.h"
#include "meshField.h"
#include "enemyState.h"
#include "enemy.h"

#define FILENAME ("asset\\model\\enemy\\brickcube.obj")

void Enemy::Init()
{
	// m_model = new Model();
	// m_model->Load(FILENAME);
	m_modelId = Model::SetModelLoadfile(FILENAME);
	Model::Load(m_modelId);
	m_position = XMFLOAT3(-20.0f, 1.0f, 1.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	m_obb = new OBB(m_position, XMFLOAT3(1.0f, 1.0f, 1.0f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	
	m_explosionSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_explosionSE->Load("asset\\audio\\se\\small_explosion1.wav");
}

void Enemy::Uninit()
{
	// m_model->Unload();
	// delete m_model;

	m_explosionSE->Play(0.1f);
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Update()
{
	MeshField* mf =  ManagerT::GetScene()->GetGameObject<MeshField>(GameObject::GOT_OBJECT3D);
	m_state.Update();
	m_rotation.y += 0.01f;
	m_rotation.z += 0.01f;

//	m_position.x = cosf(m_rotation.y) * 10.0f;
//	m_position.z = sinf(m_rotation.z * 2.0f) * 10.0f;

	m_position.y = mf->GetHeight(m_position) + 0.7f;

	m_obb->SetPosition(m_position);
}

void Enemy::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);


//	m_model->Draw();
//	Model::Draw(m_modelId);
	m_obb->SetisDraw(true);
//	m_obb->Draw();
//	m_obb->SetisDraw(false);
}
