#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "keylogger.h"
#include "obb.h"
#include "model.h"
#include "animationModel.h"
#include "bullet.h"
#include "enemy.h"
#include "enemyState.h"
#include "rock.h"
#include "camera.h"
#include "audio.h"
#include "meshField.h"
#include "playerState.h"
#include "player.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)
#define PS_NAME ("pixelLightingPS.cso")


bool GameObject::ms_IsVoidPS = false;


void Player::Init()
{
	ModelInit();

	m_position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale		= XMFLOAT3(0.01f, 0.01f, 0.01f);
	m_direction.m_forward	= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_direction.m_right		= XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_direction.m_up		= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_speed = MOVE_SPEED;

	m_obb = new OBB(m_position, m_rotation ,XMFLOAT3(1.0f, 1.7f, 1.0f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);
	m_obbAttack = nullptr;
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, PS_NAME);

	m_shotSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_shotSE->Load("asset\\audio\\se\\shot.wav");
}

void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;
	
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	m_playerState.Update();
	m_frame++;
	float frame = static_cast<float>(m_frame) * 0.7f;
	m_Model->Update(m_animationName.data(), static_cast<int>(frame));
	//m_Model->Update(m_animationName.data(),++m_frame);
//	m_Model->Update(++m_frame);
//	Jump();
	Move();
	UpdateObb();
//	ChangeCameraDir();
	Shoot();
	CollisionOther();
	// 衝突判定の後移動
	MoveFromMoveVector();
}

void Player::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_direction.m_forward.z, m_direction.m_forward.x));
	rotX *= XMMatrixRotationY(XMConvertToRadians(-90));
	//rotX = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	m_Model->Draw();
//	m_obb->SetisDraw(true);
//	m_obb->Draw();
}

void Player::Move()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if (!m_movable) return;
	XMVECTOR vPositon;
	vPositon = XMLoadFloat3(&m_position);
	XMVECTOR vForward = XMLoadFloat3(&m_direction.m_forward);
	XMVECTOR direction = vForward;

	
	if (KeyLogger_Press(KL_UP) || KeyLogger_Press(KL_DOWN) || KeyLogger_Press(KL_RIGHT) || KeyLogger_Press(KL_LEFT)) {
		if (KeyLogger_Press(KL_UP)) {
			XMFLOAT3 temp = pCamera->GetDirection()->m_forward;
			temp.y = 0.0f;
			direction += XMLoadFloat3(&temp);
			m_speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_DOWN)) {
			XMFLOAT3 temp = pCamera->GetDirection()->m_forward;
			temp.y = 0.0f;
			direction -= XMLoadFloat3(&temp);
			m_speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_RIGHT)) {
			direction += XMLoadFloat3(&pCamera->GetDirection()->m_right);
			m_speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_LEFT)) {
			direction -= XMLoadFloat3(&pCamera->GetDirection()->m_right);
			m_speed = MOVE_SPEED;
		}
		if (m_animationName != "jump") {
			m_animationName = "run";
		}
	}
	else{
		m_speed = 0.0f;
		if (m_animationName != "jump" && m_animationName != "attack") {
			m_animationName = "idle";
		}
	}

	direction = XMVector3Normalize(direction);	

	XMVECTOR cross = XMVector3Cross(vForward, direction);
	m_sign = cross.m128_f32[1] < 0.0f ? -1 : 1;

	XMVECTOR vDot = XMVector3Dot(vForward, direction);
	float fDot = 0.0f;
	XMStoreFloat(&fDot, vDot);
	float dir_difference = acosf(fDot);

	float rot = ROTATION_VALUE * m_sign;
	if (fabsf(dir_difference) <= NEARLY_ZERO_VALUE) {
		dir_difference = 0.0f;
		rot = 0.0f;
	}
	if (rot > dir_difference) {
		rot = dir_difference;
	}
	if (m_speed <= 0.0f) {
		rot = 0.0f;
	}

	XMMATRIX mtxRot;
	mtxRot = XMMatrixRotationY(rot);
	vForward = XMVector3TransformNormal(vForward, mtxRot);
	XMVECTOR vRight = XMLoadFloat3(&m_direction.m_right);
	vRight = XMVector3TransformNormal(vRight, mtxRot);
	XMStoreFloat3(&m_direction.m_forward, vForward);
	XMStoreFloat3(&m_direction.m_right, vRight);

	vDot = XMVector3Dot(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), vForward);
	XMStoreFloat(&fDot, vDot);
	m_rotation.y  = acosf(fDot);	

//	vPositon += direction * m_speed;

	MeshField* mf = ManagerT::GetScene()->GetGameObject<MeshField>(GOT_OBJECT3D);
	XMFLOAT3 tempHeight;
	XMStoreFloat3(&tempHeight, vPositon);

	XMVECTOR jumpVector = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR vGravity = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f) * GRAVITY;
	if (m_isjump) {
		XMVECTOR temp = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	
		temp= XMVector3Normalize(XMLoadFloat3(&m_direction.m_up));
		jumpVector = temp * m_jumpForce;
	//	m_jumpForce -= GRAVITY;
		temp = vPositon + jumpVector;
		if (temp.m128_f32[1] - 0.1f<= mf->GetHeight(tempHeight)) {
			m_animationName = "idle";
			m_isjump = false;
			vPositon.m128_f32[1] = mf->GetHeight(tempHeight) + 0.1f;	// 接地面+サイズ
		//	jumpVector = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		}
	}
	XMVECTOR temp = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	temp = vPositon + jumpVector + vGravity;
	if (temp.m128_f32[1] - 0.1f <= mf->GetHeight(tempHeight)) {
		vPositon.m128_f32[1] = mf->GetHeight(tempHeight) + 0.1f;	// 接地面+サイズ
		vGravity = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	}

	//if (vPositon.m128_f32[1] - 0.35f <= mf->GetHeight(tempHeight)) {
	//	vPositon.m128_f32[1] = mf->GetHeight(tempHeight) + 0.5f;	// 接地面+サイズ
	//}

	XMStoreFloat3(&m_moveVector, (direction * m_speed) + jumpVector + vGravity);
	XMStoreFloat3(&m_position, vPositon);
}

void Player::Jump()
{
	if(KeyLogger_Trigger(KL_JUMP)) {
		if (m_isjump) return;
		m_animationName = "jump";
		m_jumpForce = 0.4f;
		m_isjump = true;
	}
}

void Player::Shoot()
{
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	if (!m_isAttack && KeyLogger_Trigger(KL_ATTACK)) {
		m_animationName = "attack";
		m_isAttack = true;
		m_timerAttack = 0.0f;

		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&m_position) + XMLoadFloat3(&m_direction.m_forward) * 1;
		XMStoreFloat3(&obbPos, vObbPos);
		obbPos.y += 0.5f;
		m_obbAttack = nullptr;
		m_obbAttack = new OBB(obbPos, m_rotation, XMFLOAT3(1.0f, 0.5f,1.0f));
		ManagerT::GetScene()->AddGameObject(m_obbAttack, GameObject::GOT_OBJECT3D);
		/*
		Bullet::Create(m_position, m_direction.m_forward, 0.3f);
		m_shotSE->Play(0.1f);
		*/
	}
//	if (Input::GetMouseDown(Input::MouseButton::Left))
	if (MOUSE_TRUE)
	{
		if (Input::GetMouseTrigger(Input::MouseButton::Left))
		{
			Bullet::Create(m_position, m_direction.m_forward, 0.3f);
		}
	}

	if (m_isAttack)
	{
		m_timerAttack += 0.1f;
		// 座標更新
		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&m_position) + XMLoadFloat3(&m_direction.m_forward) * 1;
		XMStoreFloat3(&obbPos, vObbPos);
		obbPos.y += 0.5f;
		m_obbAttack->SetPosition(obbPos);

		// 敵との衝突判定
		std::vector<Enemy*> enemyList = ManagerT::GetScene()->GetGameObjects<Enemy>(GameObject::GOT_OBJECT3D);
		for (Enemy* enemy : enemyList)
		{
			if (OBB::ColOBBs(*m_obbAttack, enemy->GetObb()))
			{
				// 攻撃が当たった
				enemy->GetEnemyState()->SetIsCollided(true);
				// ガード状態なら
				if (enemy->GetEnemyState()->GetIsGuarding())
				{

				}
			}
		}

	}
	if (m_isAttack && m_timerAttack >= 10.0f)
	{
		m_isAttack = false;
		m_obbAttack->SetDead();
	}
}

void Player::CollisionOther()
{
	int isCollided = 0;
	Scene* scene = ManagerT::GetScene();
	// enemy
	std::vector<Enemy*>  enemies = scene->GetGameObjects<Enemy>(GOT_OBJECT3D);
	for (Enemy* enemy : enemies) {
		if (OBB::ColOBBs(enemy->GetObb(), GetObb())) {
		//	enemy->SetDead();
			isCollided++;
		}
	}

	// rock
	std::vector<Rock*> rocks = scene->GetGameObjects<Rock>(GOT_OBJECT3D);
	for (Rock* rock : rocks)
	{
		if (OBB::ColOBBs(rock->GetObb(), *m_obb))
		{
			isCollided++;
		}
	}


	// 何かに衝突していたら移動ベクトルを0に戻す
	if (isCollided > 0)
	{
		m_moveVector = XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
}

void Player::ChangeCameraDir()
{
	Camera* camera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if(!camera->GetMovable()){
	if (KeyLogger_Press(KL_TURN_LEFT)) {
		camera->ChangeDir(-0.02f, false);
	}
	if (KeyLogger_Press(KL_TURN_RIGHT)) {
		camera->ChangeDir(0.02f, true);
	}
	}
}

void Player::ModelInit()
{
	m_Model = new AnimationModel();

	//	m_Model->Load("asset\\model\\player\\Ch24_nonPBR.fbx");
	//m_Model->Load("asset\\model\\player\\Idle (6).fbx");	// 忍者
	m_Model->Load("asset\\model\\player\\paladin\\paladin_prop_j_nordstrom.fbx");	// 鎧
	m_animationName = "idle";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\idle.fbx", m_animationName.data());
	//m_Model->LoadAnimaiton("asset\\model\\player\\Idle.fbx", m_animationName.data());
	m_animationName = "attack";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\slash.fbx", m_animationName.data());
	//	m_Model->LoadAnimaiton("asset\\model\\player\\Stable Sword Outward Slash.fbx", m_animationName.data());
	m_animationName = "run";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\run.fbx", m_animationName.data());
	//m_Model->LoadAnimaiton("asset\\model\\player\\Run.fbx", m_animationName.data());
	m_animationName = "jump";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\jump.fbx", m_animationName.data());
	//m_Model->LoadAnimaiton("asset\\model\\player\\Jump.fbx", m_animationName.data());

	m_animationName = "idle";

}

void Player::UpdateObb()
{
	// 移動後の座標で衝突判定
	XMVECTOR vObbPos = XMLoadFloat3(&m_position) + XMLoadFloat3(&m_moveVector);
	XMFLOAT3 obbPos;
	XMStoreFloat3(&obbPos, vObbPos);
	obbPos.y += m_obb->GetLen_W(OBB::OBB_DY) * 1.0f;
	
	m_obb->SetPosition(obbPos);
	m_obb->SetRotationFromForwardRightVector(m_direction.m_forward, m_direction.m_right, m_rotation);
}

void Player::MoveFromMoveVector()
{
	XMVECTOR vPos = XMLoadFloat3(&m_position);
	vPos += XMLoadFloat3(&m_moveVector);
	XMStoreFloat3(&m_position, vPos);
}

//void Player::VoidDimension()
//{
//	if (KeyLogger_Trigger(KL_WIRE)) {
//		if (ms_IsVoidPS) {
//			ManagerT::GetScene()->AllPSChange("vertexLightingPS.cso");
//			ms_IsVoidPS = false;
//		}
//		else
//		{
//			ManagerT::GetScene()->AllPSChange("LightingVoidPS.cso");
//			ms_IsVoidPS = true;
//		}
//	}
//}
