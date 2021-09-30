#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "keylogger.h"
#include "manager.h"
#include "scene.h"
#include "obb.h"
#include "player.h"
//#include "input.h"


static float g_RoutationalSpeed;
static float g_MoveSpeed;
#define CAMERA_SPEED (0.2f)
#define AT_LENGTH (1.0f)

void Camera::Init()
{
	m_position	 = XMFLOAT3(0.0f, 4.0f, -10.0f);
	m_target	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_front		 = XMFLOAT3(0.0f, -0.3f, 1.0f);
	m_right		 = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_up		 = XMFLOAT3(0.0f, 1.0f, 0.0f);
	g_RoutationalSpeed = 0.02f;
	g_MoveSpeed = CAMERA_SPEED;
	m_isActive = false;
}

void Camera::Uninit()
{
}

void Camera::Update()
{
	
	if (KeyLogger_Trigger(KL_GUARD)) {
		if (!m_isActive) m_isActive = true;
		else m_isActive = false;
	}

	
	// 変数用意
	XMVECTOR vDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMStoreFloat3(&m_move, vDirection);
	XMVECTOR vPosition = XMLoadFloat3(&m_position);
	XMVECTOR vFront = XMLoadFloat3(&m_front);
	XMVector3Normalize(vFront);
	XMVECTOR vRight = XMLoadFloat3(&m_right);
	XMVector3Normalize(vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_up);
	XMVector3Normalize(vUp);
	XMFLOAT3 tempFront = m_front;
	tempFront.y = 0.0f;
	XMVECTOR yZeroFront = XMLoadFloat3(&tempFront);
	XMVector3Normalize(yZeroFront);
	XMVECTOR vAt = XMLoadFloat3(&m_target);

	if (m_isActive && m_movable) {

		if (KeyLogger_Press(KL_UP)) {
			vDirection += +yZeroFront;
		}
		if (KeyLogger_Press(KL_DOWN)) {
			vDirection += -yZeroFront;
		}
		if (KeyLogger_Press(KL_LEFT)) {
			vDirection += -vRight;
		}
		if (KeyLogger_Press(KL_RIGHT)) {
			vDirection += +vRight;
		}
		if (KeyLogger_Press(KL_RISE)) {
			vDirection += +vUp;
		}
		if (KeyLogger_Press(KL_FALL)) {
			vDirection += -vUp;
		}

		if (KeyLogger_Press(KL_TURN_LEFT)) {
			XMMATRIX mtxR = XMMatrixRotationY(-g_RoutationalSpeed);
			vFront = XMVector3TransformNormal(vFront, mtxR);
			vRight = XMVector3TransformNormal(vRight, mtxR);
			vUp = XMVector3Cross(vFront, vRight);
		}
		if (KeyLogger_Press(KL_TURN_RIGHT)) {
			XMMATRIX mtxR = XMMatrixRotationY(g_RoutationalSpeed);
			vFront = XMVector3TransformNormal(vFront, mtxR);
			vRight = XMVector3TransformNormal(vRight, mtxR);
			vUp = XMVector3Cross(vFront, vRight);
		}
		if (KeyLogger_Press(KL_TURN_UP)) {
			XMMATRIX mtxR = XMMatrixRotationAxis(-vRight, g_RoutationalSpeed);
			vFront = XMVector3TransformNormal(vFront, mtxR);
			vUp = XMVector3TransformNormal(vUp, mtxR);
		}
		if (KeyLogger_Press(KL_TURN_DOWN)) {
			XMMATRIX mtxR = XMMatrixRotationAxis(vRight, g_RoutationalSpeed);
			vFront = XMVector3TransformNormal(vFront, mtxR);
			vUp = XMVector3TransformNormal(vUp, mtxR);
		}
		vPosition += vDirection * CAMERA_SPEED;
		float len;  
		XMStoreFloat(&len, XMVector3Length(vDirection));
		if ( len == 0.0f) {
			g_MoveSpeed = 0.0f;
		}
		else
		{
			g_MoveSpeed = CAMERA_SPEED;
		}
	}
	else if(!m_isActive && m_movable) {
		Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
		/*XMVECTOR pFront = XMLoadFloat3(player->GetFront());
		vFront = pFront;*/
		XMVECTOR quateranion;
		XMMATRIX matTransRot;
//		if (JudgeActiveWindow()) {
		if (false) {
		
			/*if (Input::GetMouseVelocity().x >= 1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationY(g_RoutationalSpeed);
				vFront = XMVector3TransformNormal(vFront, mtxR);
				vRight = XMVector3TransformNormal(vRight, mtxR);
				vUp = XMVector3Cross(vFront, vRight);
				quateranion = XMQuaternionRotationAxis(XMVectorSet(0.0f,1.0f,0.0f,0.0f), g_RoutationalSpeed);
				matTransRot = XMMatrixRotationQuaternion(quateranion);
				vPosition = XMVector3TransformCoord(vPosition, matTransRot);
			}
			if (Input::GetMouseVelocity().x <= -1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationY(-g_RoutationalSpeed);
				vFront = XMVector3TransformNormal(vFront, mtxR);
				vRight = XMVector3TransformNormal(vRight, mtxR);
				vUp = XMVector3Cross(vFront, vRight);
				quateranion = XMQuaternionRotationAxis(XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f), -g_RoutationalSpeed);
				matTransRot = XMMatrixRotationQuaternion(quateranion);
				vPosition = XMVector3TransformCoord(vPosition, matTransRot);
			}
			if (Input::GetMouseVelocity().y >= 1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationAxis(vRight, g_RoutationalSpeed / 4);
				vFront = XMVector3TransformNormal(vFront, mtxR);
				vUp = XMVector3TransformNormal(vUp, mtxR);
				quateranion = XMQuaternionRotationAxis(vRight, g_RoutationalSpeed / 4);
				matTransRot = XMMatrixRotationQuaternion(quateranion);
				vPosition = XMVector3TransformCoord(vPosition, matTransRot);
			}
			if (Input::GetMouseVelocity().y <= -1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationAxis(vRight, -g_RoutationalSpeed / 4);
				vFront = XMVector3TransformNormal(vFront, mtxR);
				vUp = XMVector3TransformNormal(vUp, mtxR);
				quateranion = XMQuaternionRotationAxis(vRight, -g_RoutationalSpeed / 4);
				matTransRot = XMMatrixRotationQuaternion(quateranion);
				vPosition = XMVector3TransformCoord(vPosition, matTransRot);
			}
			vAt = XMLoadFloat3(&player->GetPosition());
	*/
		}

		vDirection += XMLoadFloat3(&player->GetMove());
		// プレイヤーを追いかける
		vPosition += vDirection;

		float len;
		XMStoreFloat(&len, XMVector3Length(vDirection));
		if (len == 0.0f) {
			g_MoveSpeed = 0.0f;
		}
		else
		{
			g_MoveSpeed = player->GetSpeed();
		}


	}
	else {
		// カメラが動かせない状態
	}
	// 移動
//	vPosition += vDirection * g_MoveSpeed;
	// 注視点計算

	vAt = vPosition + vFront * AT_LENGTH;

	// 変数保存
	XMStoreFloat3(&m_target, vAt);
	XMStoreFloat3(&m_position, vPosition);
	XMStoreFloat3(&m_front, vFront);
	XMStoreFloat3(&m_right, vRight);
	XMStoreFloat3(&m_up, vUp);
	XMStoreFloat3(&m_move, vDirection);

}

void Camera::Draw()
{
	// ビューマトリクス設定
	XMStoreFloat4x4(&m_viewMatrix , XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&m_up)));
	Renderer::SetViewMatrixX(&XMLoadFloat4x4(&m_viewMatrix));
	
	//D3DXMATRIX viewMatrix;
	//D3DXMatrixLookAtLH(&viewMatrix, &m_position, &m_target, &D3DXVECTOR3(0.0f,1.0f,0.0f));
	//Renderer::SetViewMatrix(&viewMatrix);

	// プロジェクションマトリクス設定
	float fov = 1.0f; //XMConvertToRadians(45.0f);
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float nearZ = 0.01f;
	float farZ = 1000.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);
	Renderer::SetProjectionMatrixX(&projMatrix);

	/*D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(&projectionMatrix);*/
}

float Camera::GetSpeed()
{
	return g_MoveSpeed;
}

void  Camera::ChangeDir(float angle, bool isRight) {

	XMVECTOR vPositon = XMLoadFloat3(&m_position);
	
	XMVECTOR vFront = XMLoadFloat3(&m_front);
	XMVector3Normalize(vFront);
	XMVECTOR vRight = XMLoadFloat3(&m_right);
	XMVector3Normalize(vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_up);
	XMVector3Normalize(vUp);	

	XMVECTOR vAt = vPositon + vFront * AT_LENGTH;


	XMMATRIX mtxR = XMMatrixRotationY(angle);
	vFront = XMVector3TransformNormal(vFront, mtxR);
	vRight = XMVector3TransformNormal(vRight, mtxR);
	vUp = XMVector3Cross(vFront, vRight);
	
	vPositon = XMLoadFloat3(&m_target) - vFront * AT_LENGTH;

	isRight = isRight;
	// if(isRight){
	// XMMATRIX mtxR = XMMatrixRotationY(angle);
	// 		vFront = XMVector3TransformNormal(vFront, mtxR);
	// 		vRight = XMVector3TransformNormal(vRight, mtxR);
	// 		vUp = XMVector3Cross(vFront, vRight);
	// }
	// else{
	// XMMATRIX mtxR = XMMatrixRotationY(angle);
	// 		vFront = XMVector3TransformNormal(vFront, mtxR);
	// 		vRight = XMVector3TransformNormal(vRight, mtxR);
	// 		vUp = XMVector3Cross(vFront, vRight);
	// }
	

	XMStoreFloat3(&m_front, vFront);
	XMStoreFloat3(&m_right, vRight);
	XMStoreFloat3(&m_up, vUp);
	XMStoreFloat3(&m_position, vPositon);
}

