#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "model.h"
#include "audio.h"
#include "obb.h"
#include "meshField.h"
#include "input.h"
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
//	m_rotation = XMFLOAT3(0.f, XMConvertToRadians(60.0f), 0.f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	m_rotationSpeed = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_right		= XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_up		= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_stateData.m_eyesight_rad = 7.0f;
	m_stateData.m_combat_rad = 3.0f;
	m_moveSpeed = 0.05f;

	m_enemyGui = new EnemyGui(this);
	m_enemyGui->Init();

	m_obb = new OBB(m_position, m_rotation, XMFLOAT3(2.1f, 2.1f, 2.1f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);

	m_state = new EnemyState(this);
	m_state->Init(GetEnemyStateData());

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	
	m_explosionSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_explosionSE->Load("asset\\audio\\se\\small_explosion1.wav");
}

void Enemy::Init(XMFLOAT3 pos, XMFLOAT3 scale)
{
	m_position = pos;
	m_obb->SetPosition(pos);
	m_scale = scale;
	XMFLOAT3 fixScale = scale;
	fixScale.x = fixScale.x * 2 + 0.1f;
	fixScale.y = fixScale.y * 2 + 0.1f;
	fixScale.z = fixScale.z * 2 + 0.1f;
	m_obb->SetScale(fixScale);
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

	m_position.y = mf->GetHeight(m_position) + m_scale.y;

	m_obb->SetPosition(m_position);
	this->UpdateRotation();
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

void Enemy::UpdateRotation()
{
	XMVECTOR vRot = XMLoadFloat3(&m_rotation);
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_rotationSpeed.y= 0.01f;
	}
	if (Input::GetKeyPress(VK_LEFT))
	{
		m_rotationSpeed.y = -0.01f;
	}
	vRot += XMLoadFloat3(&m_rotationSpeed);
	XMStoreFloat3(&m_rotation, vRot);
	XMVECTOR vFront = XMLoadFloat3(&m_front),vRight = XMLoadFloat3(&m_right),vUp;
	//	XMMATRIX mtxRot = XMMatrixRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), m_rotation.y);
	XMMATRIX mtxRot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&m_rotationSpeed));
	vFront =  XMVector3TransformNormal(vFront, mtxRot);
	vRight =  XMVector3TransformNormal(vRight, mtxRot);
	vUp = XMVector3Cross(vFront, vRight);
	XMStoreFloat3(&m_front, vFront);
	XMStoreFloat3(&m_right, vRight);
	XMStoreFloat3(&m_up, vUp);
	m_obb->SetRotation(m_rotation, m_rotationSpeed);
	//m_obb->SetRotationFromFrontRightVector(m_front, m_right, m_rotation);
}
