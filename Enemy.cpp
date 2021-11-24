#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "model.h"
#include "audio.h"
#include "obb.h"
#include "meshField.h"
#include "camera.h"
#include "enemyState.h"
#include "enemyGui.h"
#include "enemy.h"

#define FILENAME ("asset\\model\\enemy\\brickcube.obj")

void Enemy::Init()
{
	// m_model = new Model();
	// m_model->Load(FILENAME);
	m_modelId = Model::SetModelLoadfile(FILENAME);
	Model::Load(m_modelId);
	m_position = XMFLOAT3(-20.0f, 1.0f, 1.0f);
//	m_rotation = XMFLOAT3(XMConvertToRadians(45.0f), XMConvertToRadians(45.0f), XMConvertToRadians(45.0f));
	m_rotation = XMFLOAT3(0.f, XMConvertToRadians(45.0f), 0.f);
//	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	m_stateData.m_eyesight_rad = 7.0f;
	m_stateData.m_combat_rad = 3.0f;
	m_moveSpeed = 0.05f;

	m_enemyGui = new EnemyGui(this);
	m_enemyGui->Init();

	m_obb = new OBB(m_position, m_rotation, XMFLOAT3(1.1f, 1.1f, 1.1f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);

	m_state = new EnemyState(this);
	m_state->Init(GetEnemyStateData());

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	
	m_explosionSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_explosionSE->Load("asset\\audio\\se\\small_explosion1.wav");
}

void Enemy::Uninit()
{
	// m_model->Unload();
	// delete m_model;
	m_obb->SetDead();
	m_explosionSE->Play(0.1f);
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Update()
{
	MeshField* mf =  ManagerT::GetScene()->GetGameObject<MeshField>(GameObject::GOT_OBJECT3D);
	m_state->Update();
	m_rotation.y += 0.01f;
//	m_rotation.z += 0.02f;

//	m_position.x = cosf(m_rotation.y) * 10.0f;
//	m_position.z = sinf(m_rotation.z * 2.0f) * 10.0f;

	m_position.y = mf->GetHeight(m_position) + m_scale.y;

	m_obb->SetPosition(m_position);
	m_obb->SetRotation(m_rotation);
}

void Enemy::Draw()
{
	// 視錘台カリング
	Scene* scene = ManagerT::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(GOT_CAMERA);
	if (!camera->CheckView(m_position))
	{
		return;
	}

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
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


//	m_model->Draw();
	Model::Draw(m_modelId);
//	m_obb->SetisDraw(true);
//	m_obb->Draw();
//	m_obb->SetisDraw(false);
}
