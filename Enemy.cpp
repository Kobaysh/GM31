#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "Scene.h"
#include "animationModel.h"
#include "audio.h"
#include "obb.h"
#include "meshField.h"
#include "input.h"
#include "camera.h"
#include "rock.h"
#include "shaderManager.h"
#include "enemyState.h"
#include "enemyStateCombatDamaged.h"
#include "enemyBehavior.h"
#include "enemyGui.h"
#include "hp.h"
#include "trunk.h"
#include "enemyTrunkBar.h"
#include "enemy.h"

const std::string Enemy::VS_FILE_NAME = "asset/shader/toonVS.cso";	// 頂点シェーダー名
const std::string Enemy::PS_FILE_NAME = "asset/shader/toonPS.cso";	// ピクセルシェーダー名

EnemyGui* Enemy::m_EnemyGui = nullptr;								// GUIオブジェクト

Enemy::Enemy():
	m_MaxHp(3),
	m_MoveSpeed (0.0f),
	m_RotationSpeed(XMFLOAT3(0.0f,0.0f,0.0f)),
	m_StateData(0.0f, 0.0f,0.0f,0.0f,0.0f)
{
	m_NowHp = m_MaxHp;
	m_Position = (XMFLOAT3(0.0f, 0.0f, 0.0f));
}

void Enemy::Init()
{

	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);
	m_RotationSpeed = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// 各方向初期化
	m_Direction.Forward	= XMFLOAT3(0.0f, 0.0f, -1.0f);
	m_Direction.Right		= XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_Direction.Up		= XMFLOAT3(0.0f, 1.0f, 0.0f);

	m_MoveVector = XMFLOAT3(0.0f, 0.0f, 0.0f);

	// 状態変化に必要な変数初期化
	m_StateData.m_EyesightRad = 7.0f;
	m_StateData.m_CombatRad = 3.0f;

	if (m_IsUsingState)
	{
		m_State = new EnemyState();
	}
	else
	{
		m_Behavior = new EnemyBehavior();
	}
	m_MoveSpeed = 0.05f;

	// モデル読み込み
	ModelInit();

	m_Frame = 0;

	// 敵用のGUI追加
	if (!m_EnemyGui)
	{
		m_EnemyGui = new EnemyGui();
		m_EnemyGui->Init();
	}
	// 当たり判定用のOBB追加
	m_Obb = new OBB(m_Position, m_Rotation, XMFLOAT3(2.1f, 2.1f, 2.1f));
	ManagerT::GetScene()->AddGameObject(m_Obb, GOT_OBJECT3D);


	// HPバー
	m_HpBar = new HpBar();
	ManagerT::GetScene()->AddGameObject(m_HpBar, GOT_OBJECT3D)->Init(m_Position, XMFLOAT3(1.0f, 0.2f, 1.0f), m_MaxHp, m_MaxHp);

	// 体幹セット
	m_Trunk = new Trunk(30);
	m_TrunkBar = new TrunkBar();
	ManagerT::GetScene()->AddGameObject(m_TrunkBar, GOT_OBJECT3D)->Init(this);


	ShaderManager::Load(ShaderManager::Shader_Type::ST_VS, VS_FILE_NAME);
	ShaderManager::Load(ShaderManager::Shader_Type::ST_PS, PS_FILE_NAME);

	/*Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/vertexLightingPS.cso");*/

	// やられた時の爆発音
	m_explosionSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_explosionSE->Load("asset\\audio\\se\\small_explosion1.wav");
}

void Enemy::Init(XMFLOAT3 pos, XMFLOAT3 scale)
{
	m_Position = pos;
	m_Obb->SetPosition(pos);
	m_Scale = scale;
	XMFLOAT3 fixScale = scale;
	fixScale.x = fixScale.x * 2 + 0.1f;
	fixScale.y = fixScale.y * 2 + 0.1f;
	fixScale.z = fixScale.z * 2 + 0.1f;
	m_Obb->SetScale(fixScale);
	m_HpBar->SetPosition(pos);
	m_HpBar->SetScale(XMFLOAT3(1.0f, 0.3f, 1.0f));
}

void Enemy::Init(XMFLOAT3 pos, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	m_Position = pos;
	m_Obb->SetPosition(pos);
	m_Rotation = rotation;
	XMMATRIX rot = XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));
	XMVECTOR vF, vR, vU;
	vF = XMLoadFloat3(&m_Direction.Forward);
	vR = XMLoadFloat3(&m_Direction.Right);
	vF = XMVector3TransformNormal(vF, rot);
	vR = XMVector3TransformNormal(vR, rot);
	vU = XMVector3Cross(vF, vR);
	XMStoreFloat3(&m_Direction.Forward, vF);
	XMStoreFloat3(&m_Direction.Right, vR);
	XMStoreFloat3(&m_Direction.Up, vU);
	m_Obb->SetRotation(rotation, XMFLOAT3(0.0f,0.0f,0.0f));
	m_Scale = scale;
	XMFLOAT3 fixScale = scale;
	fixScale.y = fixScale.y * 1.7f + 0.1f;
	m_Obb->SetScale(fixScale);
	m_HpBar->SetPosition(pos);
	m_HpBar->SetScale(XMFLOAT3(1.0f, 0.3f, 1.0f));
}

void Enemy::Uninit()
{
	delete m_Trunk;
	if (m_IsUsingState)
	{
		delete m_State;
	}
	else
	{
		m_Behavior->Uninit();
		delete m_Behavior;
	}
	m_Obb->SetDead();
	m_HpBar->SetDead();
	m_TrunkBar->SetDead();
	m_explosionSE->Play(0.1f);
	//m_VertexLayout->Release();
	//m_VertexShader->Release();
	//m_PixelShader->Release();
}

void Enemy::Update()
{
	MeshField* mf =  ManagerT::GetScene()->GetGameObject<MeshField>(GameObject::GOT_OBJECT3D);
	m_Frame++;
	float frame = static_cast<float>(m_Frame) * 1.0f;
	m_Model->Update(m_AnimationName.data(), frame);
	if (m_IsUsingState)
	{
		m_State->Update(this);
	}
	else
	{
		m_Behavior->Upadate(this);
	}
	//	m_State->Update();
	this->UpdateOBB();
	this->CollisionOther();
	this->MoveFromMoveVector();
	if (mf)
	{
		m_Position.y = mf->GetHeight(m_Position) + m_Scale.y;
	}
	//	m_Obb->SetPosition(m_Position);

}

void Enemy::Draw()
{
	// 視錘台カリング
	Scene* scene = ManagerT::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(GOT_CAMERA);
	if (!camera->CheckView(m_Position))
	{
		return;
	}

	// 入力レイアウト設定
	VertexShaderLayout* vertexInfo = ShaderManager::GetVertexShader(VS_FILE_NAME);
	Renderer::GetpDeviceContext()->IASetInputLayout(vertexInfo->m_VertexLayout);
	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(vertexInfo->m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(ShaderManager::GetPixelShader(PS_FILE_NAME), NULL, 0);


	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX scaleFix = XMMatrixScaling(0.01f, 0.01f, 0.01f);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y - m_Scale.y, m_Position.z);
	XMMATRIX worldX = scaleX * scaleFix * rotX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	m_Model->Draw();
	//	Model::Draw(m_ModelId);
	//	m_Obb->SetisDraw(true);
	//	m_Obb->Draw();
	//	m_Obb->SetisDraw(false);
}

std::string Enemy::GetEnemyBehaviorName()
{
	return m_Behavior->GetActiveNodeName();
}

bool Enemy::Damage(int damage)
{
	if (damage < 0)return false;
	m_NowHp -= damage;
	m_HpBar->SetHP(m_NowHp, m_MaxHp);
	if (m_IsUsingState)
	{
		EnemyStatePattern* pStatePattern =
			m_State->ChangeState(new EnemyStateCombatDamaged(this));
		m_State->SetStateName("EnemyStateCombatDamaged");
		delete pStatePattern;
	}
	if (m_NowHp <= 0)
	{
		m_NowHp = 0;
		m_HpBar->SetHP(m_NowHp, m_MaxHp);
		//	SetDead();
		return true;
	}
	return false;
}

void Enemy::UpdateRotation()
{
	m_Obb->SetRotation(m_Rotation, m_RotationSpeed);
}

void Enemy::UpdateOBB()
{
	// 移動後の座標で衝突判定
	XMVECTOR vObbPos = XMLoadFloat3(&m_Position) + XMLoadFloat3(&m_MoveVector) * m_MoveSpeed;
	XMFLOAT3 obbPos;
	XMStoreFloat3(&obbPos, vObbPos);
	//	obbPos.y += m_Obb->GetLen_W(OBB::OBB_DY) * 1.0f;

	m_Obb->SetPosition(obbPos);
	this->UpdateRotation();
}

void Enemy::MoveFromMoveVector()
{
	XMVECTOR vPos = XMLoadFloat3(&m_Position);
	vPos += XMLoadFloat3(&m_MoveVector) * m_MoveSpeed;
	XMStoreFloat3(&m_Position, vPos);
	XMFLOAT3 hpBarPos = m_Position;
	hpBarPos.y += 2.0f* m_Scale.y;
	m_HpBar->SetPosition(hpBarPos);
	hpBarPos.y -= 0.4f* m_Scale.y;
	m_TrunkBar->SetPosition(hpBarPos);
}

void Enemy::CollisionOther()
{
	Scene* scene = ManagerT::GetScene();
	int isCollided = 0;
	// rock
	std::vector<Rock*> rocks = scene->GetGameObjects<Rock>(GOT_OBJECT3D);
	for (Rock* rock : rocks)
	{
		if (OBB::ColOBBs(rock->GetObb(), *m_Obb))
		{
			isCollided++;
		}
	}

	if (isCollided > 0)
	{
		this->SetMoveVector(XMFLOAT3(0.0f, 0.0f, 0.0f));
	}
}

void Enemy::ModelInit()
{
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\enemy\\ninja\\Ninja.fbx");

	m_AnimationName = "idle_idle";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\Ninja_Idle.fbx", m_AnimationName.data());

	m_AnimationName = "run";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\Run.fbx", m_AnimationName.data());

	m_AnimationName = "combat_idle";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\Combat_Idle.fbx", m_AnimationName.data());

	m_AnimationName = "kick";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\quick_kick.fbx", m_AnimationName.data());
	m_AnimationName = "back_kick";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\back_kick.fbx", m_AnimationName.data());

	m_AnimationName = "guard";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\guard.fbx", m_AnimationName.data());

	m_AnimationName = "hit_reaction";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\Hit_Reaction.fbx", m_AnimationName.data());
	m_AnimationName = "dying";
	m_Model->LoadAnimaiton("asset\\model\\enemy\\ninja\\Dying.fbx", m_AnimationName.data());

	m_AnimationName = "idle_idle";
}
