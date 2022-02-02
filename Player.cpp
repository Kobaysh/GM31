#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "keylogger.h"
#include "obb.h"
#include "model.h"
#include "animationModel.h"
#include "enemy.h"
#include "enemyState.h"
#include "rock.h"
#include "camera.h"
#include "audio.h"
#include "meshField.h"
#include "lockOnCircle.h"
#include "trunk.h"
#include "playerState.h"
#include "player_hp.h"
#include "player.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)
#define PS_NAME ("asset/shader/pixelLightingPS.cso")


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
	m_timerAttack = 0.0f;
	m_timerGuard = 0.0f;
	m_maxHp = m_nowHp = 10;

	m_obb = new OBB(m_position, m_rotation ,XMFLOAT3(1.0f, 1.7f, 1.0f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);
	m_obbAttack = nullptr;

	m_trunk = new Trunk(100);

	m_hpBar = new HpPlayer();
	ManagerT::GetScene()->AddGameObject(m_hpBar, GOT_OBJECT2D)->Init(XMFLOAT3(20.0f, SCREEN_HEIGHT * 0.97f, 1.0f), XMFLOAT3(50.0f, 10.0f, 1.0f), m_nowHp, m_maxHp);

	m_lockOnRad = 10.0f;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, PS_NAME);

	m_shotSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_shotSE->Load("asset\\audio\\se\\shot.wav");
}

void Player::Uninit()
{
	delete m_trunk;
	m_obb->SetDead();
	if (m_hpBar)
	{
		m_hpBar->SetDead();
	}
	if (m_Model)
	{
		m_Model->Unload();
		delete m_Model;
		m_Model = nullptr;
	}
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
	this->Move();
	this->UpdateObb();
//	this->ChangeCameraDir();
	this->Slash();
	this->Guard();
	this->LockOn();
//	this->Shoot();
	this->CollisionOther();
	// 衝突判定の後移動
	this->MoveFromMoveVector();
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
	// デバッグ用OBB表示
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
		if (m_animationName != "jump")
		{
			if (m_animationName != "run")
			{
				this->ChangeAnimation("run");
			}
		}
	}
	else{
		m_speed = 0.0f;
		if (m_animationName != "jump" && m_animationName != "attack" && !m_isGuard) {
			if (m_animationName != "idle")
			{
				this->ChangeAnimation("idle");
			}
		}
	}

	direction = XMVector3Normalize(direction);	

	// 回転処理
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

	// ジャンプとフィールド上処理
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
			if(m_animationName != "idle"){
			this->ChangeAnimation("idle");
			//	m_animationName = "idle";
			}
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
		this->ChangeAnimation("jump");
		m_jumpForce = 0.4f;
		m_isjump = true;
	}
}

void Player::Slash()
{
	// 攻撃
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	if (MOUSE_ACTIVE)
	{

		if (!m_isAttack &&Input::GetMouseTrigger(Input::MouseButton::Left))
		{
			this->ChangeAnimation("attack");
			m_isAttack = true;
			m_timerAttack = 0.0f;
			XMFLOAT3 obbPos;
			XMVECTOR vObbPos = XMLoadFloat3(&m_position) + XMLoadFloat3(&m_direction.m_forward) * 1;
			XMStoreFloat3(&obbPos, vObbPos);
			obbPos.y += 0.5f;
			m_obbAttack = nullptr;
			m_obbAttack = new OBB(obbPos, m_rotation, XMFLOAT3(1.0f, 0.5f,1.5f));
			ManagerT::GetScene()->AddGameObject(m_obbAttack, GameObject::GOT_OBJECT3D);
		}
	}
	else if (!m_isAttack && KeyLogger_Trigger(KL_ATTACK)) 
	{
		this->ChangeAnimation("attack");
		m_isAttack = true;
		m_timerAttack = 0.0f;

		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&m_position) + XMLoadFloat3(&m_direction.m_forward) * 1;
		XMStoreFloat3(&obbPos, vObbPos);
		obbPos.y += 0.5f;
		m_obbAttack = nullptr;
		m_obbAttack = new OBB(obbPos, m_rotation, XMFLOAT3(1.0f, 0.5f,1.5f));
		ManagerT::GetScene()->AddGameObject(m_obbAttack, GameObject::GOT_OBJECT3D);
	}
	//	if (Input::GetMouseDown(Input::MouseButton::Left))


	if (m_isAttack)
	{
		m_timerAttack += 0.1f;
		// 座標更新
		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&m_position) + XMLoadFloat3(&m_direction.m_forward) * 1;
		XMStoreFloat3(&obbPos, vObbPos);
		obbPos.y += 0.5f;
		m_obbAttack->SetPosition(obbPos);

		if (m_timerAttack >= 4.0f)
		{
			// 敵との衝突判定
			std::vector<Enemy*> enemyList = ManagerT::GetScene()->GetGameObjects<Enemy>(GameObject::GOT_OBJECT3D);
			for (Enemy* enemy : enemyList)
			{
				if (OBB::ColOBBs(*m_obbAttack, enemy->GetObb())){
					if (enemy->GetIsUsingState()){
						// 攻撃が当たった
						enemy->GetEnemyState()->SetIsCollided(true);
						if (enemy->GetTrunk()->GetIsCollapsed()){
							// 体幹が崩れているなら即死
							enemy->Damage(99999999);
						}
						else{
							// ガード状態なら
							if (enemy->GetEnemyState()->GetIsGuarding()){
								// 体幹にダメージ
								enemy->GetTrunk()->ChangeNowTrunk(10);
							}
							else{
								if (enemy->Damage(1)){
									// 止めを刺す
								}
								else{
									// 体幹にダメージ
									enemy->GetTrunk()->ChangeNowTrunk(10);
								}
							}
						}

						m_isAttack = false;
						this->ChangeAnimation("idle");
						//	m_animationName = "idle";
						m_obbAttack->SetDead();
					}
				}
			}
		}

	}
	if (m_isAttack && m_timerAttack >= 10.0f)
	{
		m_isAttack = false;
		this->ChangeAnimation("idle");
		//	m_animationName = "idle";
		m_obbAttack->SetDead();
	}
}

void Player::Shoot()
{
	// 弾を撃つ
	//if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	//if (KeyLogger_Trigger(KL_GUARD)) {
	//	
	//	Bullet::Create(m_position, m_direction.m_forward, 0.3f);
	//	m_shotSE->Play(0.1f);
	//	
	//}
}

void Player::Guard()
{
	// 防御
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	if (MOUSE_ACTIVE)
	{
		if (!m_isAttack && !m_isGuard && Input::GetMouseTrigger(Input::MouseButton::Right))
		{
			m_isGuard = true;
			m_timerGuard = 0.0f;
			this->ChangeAnimation("guard_start");
		}
		else if (m_isGuard && Input::GetKeyPress(Input::MouseButton::Right))
		{
			if (m_timerGuard >= 1.0f)
			{
				if(m_animationName != "guard_idle")
					this->ChangeAnimation("guard_idle");
			}
			m_timerGuard += 0.1f;
		}
		else if (m_isGuard && Input::GetMouseUp(Input::MouseButton::Right))
		{
			m_isGuard = false;
		}
	}
	else
	{
		if (!m_isAttack && !m_isGuard && KeyLogger_Trigger(KL_GUARD))
		{
			m_isGuard = true;
			m_timerGuard = 0.0f;
			this->ChangeAnimation("guard_start");
		}
		else if (m_isGuard && KeyLogger_Press(KL_GUARD))
		{
			if (m_timerGuard >= 1.0f)
			{
				if(m_animationName != "guard_idle")
				this->ChangeAnimation("guard_idle");
			}
			m_timerGuard += 0.1f;		}
		else if (m_isGuard && KeyLogger_Release(KL_GUARD))
		{
			m_isGuard = false;
		}
	}
}

void Player::LockOn()
{	
	bool on = false;
	if (MOUSE_ACTIVE)
	{
		on = Input::GetMouseTrigger(Input::MouseButton::Center);
	}
	if (KeyLogger_Trigger(KL_LOCKON) || on)
	{
		Scene* scene = ManagerT::GetScene();
		Camera* camera = scene->GetGameObject<Camera>(GOT_CAMERA);
		if (camera->GetIsLock())
		{
			camera->SetIsLock(false);
			if (m_lockOnCircle)
			{
				m_lockOnCircle->SetDead();
				m_lockOnCircle = nullptr;
			}
			return;
		}
		std::vector<Enemy*>  enemies = scene->GetGameObjects<Enemy>(GOT_OBJECT3D);
		std::sort(enemies.begin(), enemies.end(), [this](Enemy* e1, Enemy* e2) {
			XMVECTOR vPPos, vEPos1, vEPos2;
			vPPos = XMLoadFloat3(&GetPosition());
			vEPos1 = XMLoadFloat3(&e1->GetPosition());
			vEPos2 = XMLoadFloat3(&e2->GetPosition());
			float distance1, distance2;
			XMStoreFloat(&distance1, XMVector3Length(vPPos - vEPos1));
			XMStoreFloat(&distance2, XMVector3Length(vPPos - vEPos2));

			return (distance1 > distance2);
			});
		for (auto enemy : enemies)
		{
			XMVECTOR vPPos, vEPos;
			vPPos = XMLoadFloat3(&GetPosition());
			vEPos = XMLoadFloat3(&enemy->GetPosition());
			float distance;
			XMStoreFloat(&distance, XMVector3Length(vPPos - vEPos));
			if (distance <= m_lockOnRad)
			{
				camera->SetIsLock(true);
				camera->SetLockTarget(enemy->GetpPosition());
				m_lockOnCircle = new LockOnCircle(enemy);
				scene->AddGameObject(m_lockOnCircle, GOT_OBJECT2D);
				break;
			}
		}
		
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

bool Player::Damage(int damage)
{
	if (damage < 0)return false;
	m_nowHp -= damage;
	m_hpBar->SetHP(m_nowHp, m_maxHp);
	if (m_nowHp <= 0)
	{
		m_nowHp = 0;
		m_hpBar->SetHP(m_nowHp, m_maxHp);
		SetDead();
		return true;
	}
	return false;
}

void Player::ModelInit()
{
	m_Model = new AnimationModel();

	//m_Model->Load("asset\\model\\player\\Ch24_nonPBR.fbx");
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
	m_animationName = "guard_start";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\guard_start.fbx", m_animationName.data());
	m_animationName = "guard_idle";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\guard_idle.fbx", m_animationName.data());

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

void Player::ChangeAnimation(const char * animationName)
{
	m_animationName = animationName;
	m_frame = 0;
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
