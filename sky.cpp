#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "bullet.h"
#include "sky.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)


void Sky::Init()
{
	m_Model = new Model();
//	m_Model->Load("asset\\model\\torus\\torus.obj"); // \\か//しか使えない
//	m_Model->Load("asset\\model\\bricktorus\\bricktorus.obj");	 // \\か//しか使えない
//	m_Model->Load("asset\\model\\test\\DX.obj");	 // \\か//しか使えない
	m_Model->Load("asset\\model\\sky\\skydome.obj");	 // \\か//しか使えない
	

	m_Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(100.0f, 100.0f, 100.0f);
	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_speed = MOVE_SPEED;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}

void Sky::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Sky::Update()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	XMVECTOR vPos = XMLoadFloat3(&m_Position);
	// カメラ移動に併せて移動
	if (pCamera->GetIsActive()) {
		XMVECTOR cameraFront = XMLoadFloat3(pCamera->GetMove());
		cameraFront.m128_f32[1] = 0.0f;
		vPos += cameraFront * pCamera->GetSpeed();
	}
	else {
		vPos += XMLoadFloat3(&ManagerT::GetScene()->GetGameObject<Player>(GOT_OBJECT3D)->GetMove());
	}
	XMStoreFloat3(&m_Position, vPos);
}

void Sky::Draw()
{

    

//	XMFLOAT4X4 fCamera;
//	XMStoreFloat4x4(&fCamera, mCamera);
//	XMFLOAT4X4 temp;
//	XMStoreFloat4x4(&temp, XMMatrixIdentity());
//	/*temp._41 = -fCamera._43;
//	temp._42 = -fCamera._42;
//	temp._43 = fCamera._41;*/
//
//	temp._41 = -fCamera._41;
////	temp._42 = fCamera._42;
//	temp._43 = -fCamera._43;
//
//	mCamera = XMLoadFloat4x4(&temp);
////	mCamera = XMLoadFloat4x4(&fCamera);
//
////	mCamera *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//	
	
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_front.z, m_front.x));
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX* rotX /**mCamera*/ *transX;
	Renderer::SetWorldMatrixX(&worldX);


	m_Model->Draw();
}

void Sky::Move()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if (pCamera->GetIsActive()) return;
	//XMVECTOR direction = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR vPositon;
	vPositon = XMLoadFloat3(&m_Position);
	XMVECTOR vFront = XMLoadFloat3(&m_front);
	XMVECTOR direction = vFront;
	if (KeyLogger_Press(KL_UP) || KeyLogger_Press(KL_DOWN) || KeyLogger_Press(KL_RIGHT) || KeyLogger_Press(KL_LEFT)) {
		direction = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
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
	XMStoreFloat3(&m_moveVector, (direction * m_speed));
	XMStoreFloat3(&m_Position, vPositon);
}

void Sky::Shoot()
{
	if (ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA)->GetIsActive()) return;

	if (KeyLogger_Trigger(KL_FIRE)) {
		Bullet::Create(m_Position, m_front, 0.3f);
	}
}

void Sky::VoidDimension()
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
