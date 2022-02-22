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
#include "player_hp.h"
#include "player.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)
#define PS_NAME ("asset/shader/pixelLightingPS.cso")


void Player::Init()
{
	ModelInit();

	m_Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(0.01f, 0.01f, 0.01f);
	m_Direction.Forward	= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_Direction.Right	= XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_Direction.Up		= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Speed = MOVE_SPEED;
	m_TimerAttack = 0.0f;
	m_TimerGuard = 0.0f;
	m_MaxHp = m_NowHp = 10;

	m_Obb = new OBB(m_Position, m_Rotation ,XMFLOAT3(1.0f, 1.7f, 1.0f));
	ManagerT::GetScene()->AddGameObject(m_Obb, GOT_OBJECT3D);
	m_ObbAttack = nullptr;

	m_Trunk = new Trunk(100);

	m_HpBar = new HpPlayer();
	ManagerT::GetScene()->AddGameObject(m_HpBar, GOT_OBJECT2D)->Init(XMFLOAT3(20.0f, SCREEN_HEIGHT * 0.97f, 1.0f), XMFLOAT3(50.0f, 10.0f, 1.0f), m_NowHp, m_MaxHp);

	m_LockOnRad = 10.0f;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/pixelLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, PS_NAME);

	m_SlashSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_SlashSE->Load("asset\\audio\\se\\slash.wav");
}

void Player::Uninit()
{
	delete m_Trunk;
	m_Obb->SetDead();
	if (m_HpBar)
	{
		m_HpBar->SetDead();
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
	m_Frame++;
	float frame = static_cast<float>(m_Frame) * 0.7f;
	m_Model->Update(m_AnimationName.data(), static_cast<int>(frame));
	//m_Model->Update(m_AnimationName.data(),++m_Frame);
	//	m_Model->Update(++m_Frame);
	//	Jump();
	this->Move();
	this->UpdateObb();
	this->Slash();
	this->Guard();
	this->LockOn();
	this->CollisionOther();
	// 衝突判定の後移動
	this->MoveFromMoveVector();
	this->MouseActive();
}

void Player::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_Direction.Forward.z, m_Direction.Forward.x));
	rotX *= XMMatrixRotationY(XMConvertToRadians(-90));
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	m_Model->Draw();
	// デバッグ用OBB表示
	//	m_Obb->SetisDraw(true);
	//	m_Obb->Draw();
}

void Player::Move()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if (!m_IsMovable) return;
	XMVECTOR vPositon;
	vPositon = XMLoadFloat3(&m_Position);
	XMVECTOR vForward = XMLoadFloat3(&m_Direction.Forward);
	XMVECTOR direction = vForward;


	if (KeyLogger_Press(KL_UP) || KeyLogger_Press(KL_DOWN) || KeyLogger_Press(KL_RIGHT) || KeyLogger_Press(KL_LEFT)) {
		if (KeyLogger_Press(KL_UP)) {
			XMFLOAT3 temp = pCamera->GetDirection()->Forward;
			temp.y = 0.0f;
			direction += XMLoadFloat3(&temp);
			m_Speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_DOWN)) {
			XMFLOAT3 temp = pCamera->GetDirection()->Forward;
			temp.y = 0.0f;
			direction -= XMLoadFloat3(&temp);
			m_Speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_RIGHT)) {
			direction += XMLoadFloat3(&pCamera->GetDirection()->Right);
			m_Speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_LEFT)) {
			direction -= XMLoadFloat3(&pCamera->GetDirection()->Right);
			m_Speed = MOVE_SPEED;
		}
		if (m_AnimationName != "jump")
		{
			if (m_AnimationName != "run")
			{
				this->ChangeAnimation("run");
			}
		}
	}
	else{
		m_Speed = 0.0f;
		if (m_AnimationName != "jump" && m_AnimationName != "attack" && !m_IsGuard) {
			if (m_AnimationName != "idle")
			{
				this->ChangeAnimation("idle");
			}
		}
	}

	direction = XMVector3Normalize(direction);	

	// 回転処理
	XMVECTOR cross = XMVector3Cross(vForward, direction);
	m_Sign = cross.m128_f32[1] < 0.0f ? -1 : 1;

	XMVECTOR vDot = XMVector3Dot(vForward, direction);
	float fDot = 0.0f;
	XMStoreFloat(&fDot, vDot);
	float dir_difference = acosf(fDot);

	float rot = ROTATION_VALUE * m_Sign;
	if (fabsf(dir_difference) <= NEARLY_ZERO_VALUE) {
		dir_difference = 0.0f;
		rot = 0.0f;
	}
	if (rot > dir_difference) {
		rot = dir_difference;
	}
	if (m_Speed <= 0.0f) {
		rot = 0.0f;
	}

	XMMATRIX mtxRot;
	mtxRot = XMMatrixRotationY(rot);
	vForward = XMVector3TransformNormal(vForward, mtxRot);
	XMVECTOR vRight = XMLoadFloat3(&m_Direction.Right);
	vRight = XMVector3TransformNormal(vRight, mtxRot);
	XMStoreFloat3(&m_Direction.Forward, vForward);
	XMStoreFloat3(&m_Direction.Right, vRight);

	vDot = XMVector3Dot(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), vForward);
	XMStoreFloat(&fDot, vDot);
	m_Rotation.y  = acosf(fDot);	

	//	vPositon += direction * m_Speed;

	// ジャンプとフィールド上処理
	MeshField* mf = ManagerT::GetScene()->GetGameObject<MeshField>(GOT_OBJECT3D);
	XMFLOAT3 tempHeight;
	XMStoreFloat3(&tempHeight, vPositon);

	XMVECTOR jumpVector = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR vGravity = XMVectorSet(0.0f, -1.0f, 0.0f, 0.0f) * GRAVITY;
	if (m_Isjump) {
		XMVECTOR temp = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);


		temp= XMVector3Normalize(XMLoadFloat3(&m_Direction.Up));
		jumpVector = temp * m_JumpForce;
		//	m_JumpForce -= GRAVITY;
		temp = vPositon + jumpVector;
		if (temp.m128_f32[1] - 0.1f<= mf->GetHeight(tempHeight)) {
			if(m_AnimationName != "idle"){
				this->ChangeAnimation("idle");
				//	m_AnimationName = "idle";
			}
			m_Isjump = false;
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

	XMStoreFloat3(&m_MoveVector, (direction * m_Speed) + jumpVector + vGravity);
	XMStoreFloat3(&m_Position, vPositon);
}

void Player::Jump()
{
	if(KeyLogger_Trigger(KL_JUMP)) {
		if (m_Isjump) return;
		this->ChangeAnimation("jump");
		m_JumpForce = 0.4f;
		m_Isjump = true;
	}
}

void Player::Slash()
{
	// 攻撃
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	if (Input::GetMouseActive())
	{

		if (!m_IsAttack &&Input::GetMouseTrigger(Input::MouseButton::Left))
		{
			this->ChangeAnimation("attack");
			m_IsAttack = true;
			m_TimerAttack = 0.0f;
			XMFLOAT3 obbPos;
			XMVECTOR vObbPos = XMLoadFloat3(&m_Position) + XMLoadFloat3(&m_Direction.Forward) * 1;
			XMStoreFloat3(&obbPos, vObbPos);
			obbPos.y += 0.5f;
			m_ObbAttack = nullptr;
			m_ObbAttack = new OBB(obbPos, m_Rotation, XMFLOAT3(1.0f, 0.5f,1.5f));
			ManagerT::GetScene()->AddGameObject(m_ObbAttack, GameObject::GOT_OBJECT3D);
		}
	}
	else if (!m_IsAttack && KeyLogger_Trigger(KL_ATTACK)) 
	{
		this->ChangeAnimation("attack");
		m_IsAttack = true;
		m_TimerAttack = 0.0f;

		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&m_Position) + XMLoadFloat3(&m_Direction.Forward) * 1;
		XMStoreFloat3(&obbPos, vObbPos);
		obbPos.y += 0.5f;
		m_ObbAttack = nullptr;
		m_ObbAttack = new OBB(obbPos, m_Rotation, XMFLOAT3(1.0f, 0.5f,1.5f));
		ManagerT::GetScene()->AddGameObject(m_ObbAttack, GameObject::GOT_OBJECT3D);
	}
	//	if (Input::GetMouseDown(Input::MouseButton::Left))


	if (m_IsAttack)
	{
		m_TimerAttack += 0.1f;
		// 座標更新
		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&m_Position) + XMLoadFloat3(&m_Direction.Forward) * 1;
		XMStoreFloat3(&obbPos, vObbPos);
		obbPos.y += 0.5f;
		m_ObbAttack->SetPosition(obbPos);

		if (m_TimerAttack >= 4.0f)
		{
			// 敵との衝突判定
			std::vector<Enemy*> enemyList = ManagerT::GetScene()->GetGameObjects<Enemy>(GameObject::GOT_OBJECT3D);
			for (Enemy* enemy : enemyList)
			{
				if (OBB::ColOBBs(*m_ObbAttack, enemy->GetObb())){
					if (enemy->GetIsUsingState()){
						// 攻撃が当たった
						m_SlashSE->Play();
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

						m_IsAttack = false;
						this->ChangeAnimation("idle");
						//	m_AnimationName = "idle";
						m_ObbAttack->SetDead();
					}
				}
			}
		}

	}
	if (m_IsAttack && m_TimerAttack >= 10.0f)
	{
		m_IsAttack = false;
		this->ChangeAnimation("idle");
		//	m_AnimationName = "idle";
		m_ObbAttack->SetDead();
	}
}

void Player::Shoot()
{
	// 弾を撃つ
	//if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	//if (KeyLogger_Trigger(KL_GUARD)) {
	//	
	//	Bullet::Create(m_Position, m_Direction.Forward, 0.3f);
	//	m_SlashSE->Play(0.1f);
	//	
	//}
}

void Player::Guard()
{
	// 防御
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetMovable()) return;

	if (Input::GetMouseActive())
	{
		if (!m_IsAttack && !m_IsGuard && Input::GetMouseTrigger(Input::MouseButton::Right))
		{
			m_IsGuard = true;
			m_TimerGuard = 0.0f;
			this->ChangeAnimation("guard_start");
		}
		else if (m_IsGuard && Input::GetMouseDown(Input::MouseButton::Right))
		{
			if (m_TimerGuard >= 1.0f)
			{
				if(m_AnimationName != "guard_idle")
					this->ChangeAnimation("guard_idle");
			}
			m_TimerGuard += 0.1f;
		}
		else if (m_IsGuard && Input::GetMouseUp(Input::MouseButton::Right))
		{
			m_IsGuard = false;
		}
	}
	else
	{
		if (!m_IsAttack && !m_IsGuard && KeyLogger_Trigger(KL_GUARD))
		{
			m_IsGuard = true;
			m_TimerGuard = 0.0f;
			this->ChangeAnimation("guard_start");
		}
		else if (m_IsGuard && KeyLogger_Press(KL_GUARD))
		{
			if (m_TimerGuard >= 1.0f)
			{
				if(m_AnimationName != "guard_idle")
					this->ChangeAnimation("guard_idle");
			}
			m_TimerGuard += 0.1f;		}
		else if (m_IsGuard && KeyLogger_Release(KL_GUARD))
		{
			m_IsGuard = false;
		}
	}
}

void Player::LockOn()
{	
	bool on = false;
	if (Input::GetMouseActive())
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
			if (m_LockOnCircle)
			{
				m_LockOnCircle->SetDead();
				m_LockOnCircle = nullptr;
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
			if (distance <= m_LockOnRad)
			{
				camera->SetIsLock(true);
				camera->SetLockTarget(enemy->GetpPosition());
				m_LockOnCircle = new LockOnCircle(enemy);
				scene->AddGameObject(m_LockOnCircle, GOT_OBJECT2D);
				break;
			}
		}

	}
}

void Player::MouseActive()
{
	if (Input::GetKeyTrigger(VK_F1))
	{
		Input::SetMouseActive(!Input::GetMouseActive());
		ShowCursor(!Input::GetMouseActive());
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
		if (OBB::ColOBBs(rock->GetObb(), *m_Obb))
		{
			isCollided++;
		}
	}


	// 何かに衝突していたら移動ベクトルを0に戻す
	if (isCollided > 0)
	{
		m_MoveVector = XMFLOAT3(0.0f, 0.0f, 0.0f);
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
	m_NowHp -= damage;
	m_HpBar->SetHP(m_NowHp, m_MaxHp);
	if (m_NowHp <= 0)
	{
		m_NowHp = 0;
		m_HpBar->SetHP(m_NowHp, m_MaxHp);
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
	m_AnimationName = "idle";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\idle.fbx", m_AnimationName.data());
	//m_Model->LoadAnimaiton("asset\\model\\player\\Idle.fbx", m_AnimationName.data());
	m_AnimationName = "attack";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\slash.fbx", m_AnimationName.data());
	//	m_Model->LoadAnimaiton("asset\\model\\player\\Stable Sword Outward Slash.fbx", m_AnimationName.data());
	m_AnimationName = "run";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\run.fbx", m_AnimationName.data());
	//m_Model->LoadAnimaiton("asset\\model\\player\\Run.fbx", m_AnimationName.data());
	m_AnimationName = "jump";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\jump.fbx", m_AnimationName.data());
	//m_Model->LoadAnimaiton("asset\\model\\player\\Jump.fbx", m_AnimationName.data());
	m_AnimationName = "guard_start";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\guard_start.fbx", m_AnimationName.data());
	m_AnimationName = "guard_idle";
	m_Model->LoadAnimaiton("asset\\model\\player\\paladin\\guard_idle.fbx", m_AnimationName.data());

	m_AnimationName = "idle";

}

void Player::UpdateObb()
{
	// 移動後の座標で衝突判定
	XMVECTOR vObbPos = XMLoadFloat3(&m_Position) + XMLoadFloat3(&m_MoveVector);
	XMFLOAT3 obbPos;
	XMStoreFloat3(&obbPos, vObbPos);
	obbPos.y += m_Obb->GetLen_W(OBB::OBB_DY) * 1.0f;

	m_Obb->SetPosition(obbPos);
	m_Obb->SetRotationFromForwardRightVector(m_Direction.Forward, m_Direction.Right, m_Rotation);
}

void Player::MoveFromMoveVector()
{
	XMVECTOR vPos = XMLoadFloat3(&m_Position);
	vPos += XMLoadFloat3(&m_MoveVector);
	XMStoreFloat3(&m_Position, vPos);
}

void Player::ChangeAnimation(const char * animationName)
{
	m_AnimationName = animationName;
	m_Frame = 0;
}
