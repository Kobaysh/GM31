#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "obb.h"
#include "model.h"
#include "bullet.h"
#include "enemy.h"
#include "camera.h"
#include "audio.h"
#include "playerState.h"
#include "player.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)


bool GameObject::ms_IsVoidPS = false;


void Player::Init()
{
	m_Model = new Model();
//	m_Model->Load("asset\\model\\torus\\torus.obj"); // \\か//しか使えない
//	m_Model->Load("asset\\model\\bricktorus\\bricktorus.obj");	 // \\か//しか使えない
//	m_Model->Load("asset\\model\\test\\DX.obj");	 // \\か//しか使えない
	m_Model->Load("asset\\model\\test\\woodcube.obj");	 // \\か//しか使えない
	

	m_Position	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_up		= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_speed = MOVE_SPEED;

	m_obb = new OBB(m_Position, XMFLOAT3(1.0f, 1.0f, 1.0f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

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
	Jump();
	Move();
//	ChangeCameraDir();
	Shoot();
	CollisionOther();
	VoidDimension();
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
	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_front.z, m_front.x));
	float a= -atan2f(m_front.z, m_front.x);
	//rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);


	m_Model->Draw();
}

void Player::Move()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if (pCamera->GetIsActive()) return;
	//XMVECTOR direction = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR vPositon;
	vPositon = XMLoadFloat3(&m_Position);
	XMVECTOR vFront = XMLoadFloat3(&m_front);
	XMVECTOR direction = vFront;

	
	if (KeyLogger_Press(KL_UP) || KeyLogger_Press(KL_DOWN) || KeyLogger_Press(KL_RIGHT) || KeyLogger_Press(KL_LEFT)) {
//		direction = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		if (KeyLogger_Press(KL_UP)) {
			XMFLOAT3 temp = *pCamera->GetFront();
			temp.y = 0.0f;
			direction += XMLoadFloat3(&temp);
			m_speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_DOWN)) {
			XMFLOAT3 temp = *pCamera->GetFront();
			temp.y = 0.0f;
			direction -= XMLoadFloat3(&temp);
			m_speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_RIGHT)) {
			direction += XMLoadFloat3(pCamera->GetRight());
			m_speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_LEFT)) {
			direction -= XMLoadFloat3(pCamera->GetRight());
			m_speed = MOVE_SPEED;
		}
	}
	else{
		m_speed = 0.0f;
	}

	direction = XMVector3Normalize(direction);	

	XMVECTOR cross = XMVector3Cross(vFront, direction);
	m_sign = cross.m128_f32[1] < 0.0f ? -1 : 1;

	XMVECTOR dot = XMVector3Dot(vFront, direction);
	float fDot = 0.0f;
	XMStoreFloat(&fDot, dot);
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
	vFront = XMVector3TransformNormal(vFront, mtxRot);
	XMStoreFloat3(&m_front, vFront);

	

	vPositon += direction * m_speed;

	if (m_isjump) {
		XMVECTOR tempDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		XMFLOAT3 temp = m_up;

	
		tempDir = XMVector3Normalize(XMLoadFloat3(&temp));
		vPositon += tempDir * m_jumpForce;
		m_jumpForce -= GRAVITY;
		if (vPositon.m128_f32[1] <= 0.0f) {
			m_isjump = false;
		}
	}
	if (vPositon.m128_f32[1] - m_Scale.y <= 0.0f) {
		vPositon.m128_f32[1] = m_Scale.y + 0.0f;	// 接地面+サイズ
	}

	XMStoreFloat3(&m_moveVector, (direction * m_speed));
	XMStoreFloat3(&m_Position, vPositon);
	m_obb->SetPosition(m_Position);
}

void Player::Jump()
{
	if(KeyLogger_Trigger(KL_JUMP)) {
		if (m_isjump) return;
		m_jumpForce = 0.5f;
		m_isjump = true;
	}
}

void Player::Shoot()
{
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetIsActive()) return;

	if (KeyLogger_Trigger(KL_ATTACK)) {
		Bullet::Create(m_Position, m_front, 0.3f);
		m_shotSE->Play(0.1f);
	}
}

void Player::CollisionOther()
{
	std::vector<Enemy*>  enemies = ManagerT::GetScene()->GetGameObjects<Enemy>(GOT_OBJECT3D);
	for (Enemy* enemy : enemies) {
		if (OBB::ColOBBs(enemy->GetObb(), GetObb())) {
			enemy->SetDead();
		}
	}
}

void Player::ChangeCameraDir()
{
	Camera* camera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if(!camera->GetIsActive()){
	if (KeyLogger_Press(KL_TURN_LEFT)) {
		camera->ChangeDir(-0.02f, false);
	}
	if (KeyLogger_Press(KL_TURN_RIGHT)) {
		camera->ChangeDir(0.02f, true);
	}
	}
}

void Player::VoidDimension()
{
	if (KeyLogger_Trigger(KL_WIRE)) {
		if (ms_IsVoidPS) {
			ManagerT::GetScene()->AllPSChange("vertexLightingPS.cso");
			ms_IsVoidPS = false;
		}
		else
		{
			ManagerT::GetScene()->AllPSChange("LightingVoidPS.cso");
			ms_IsVoidPS = true;
		}
	}
}
