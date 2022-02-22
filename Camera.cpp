#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "keylogger.h"
#include "manager.h"
#include "scene.h"
#include "obb.h"
#include "player.h"
#include "input.h"


float Camera::m_RoutationalSpeed;

const  float Camera::m_CameraSpeedFirst = 0.2f;
const  float Camera::m_AtLength = 3.0f;




void Camera::Init()
{
	m_Position	 = XMFLOAT3(0.0f, 4.0f, -10.0f);
	m_Target	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Direction.Forward	 = XMFLOAT3(0.0f, -0.3f, 1.0f);
	m_Direction.Right		 = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_Direction.Up		 = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_RoutationalSpeed = 0.08f;
	m_MoveSpeed = m_CameraSpeedFirst;
	m_IsActive = true;
	m_IsLock = false;
}

void Camera::Init(bool active, bool movable)
{
	m_Position	 = XMFLOAT3(0.0f, 4.0f, -10.0f);
	m_Target	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Direction.Forward	 = XMFLOAT3(0.0f, -0.3f, 1.0f);
	m_Direction.Right		 = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_Direction.Up		 = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_RoutationalSpeed = 0.08f;
	m_MoveSpeed = m_CameraSpeedFirst;
	m_IsActive = active;
	m_IsMovable = movable;
}

void Camera::Uninit()
{
}

void Camera::Update()
{


	//if (KeyLogger_Trigger(KL_GUARD))
	//{
	//	ChangeMovableWithPlayer(!m_IsMovable);
	//}


	// 変数用意
	XMVECTOR vDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMStoreFloat3(&m_Move, vDirection);
	XMVECTOR vPosition = XMLoadFloat3(&m_Position);
	XMVECTOR vForward = XMLoadFloat3(&m_Direction.Forward);
	XMVector3Normalize(vForward);
	XMVECTOR vRight = XMLoadFloat3(&m_Direction.Right);
	XMVector3Normalize(vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_Direction.Up);
	XMVector3Normalize(vUp);
	XMFLOAT3 tempFront = m_Direction.Forward;
	tempFront.y = 0.0f;
	XMVECTOR yZeroFront = XMLoadFloat3(&tempFront);
	XMVector3Normalize(yZeroFront);
	XMVECTOR vAt = XMLoadFloat3(&m_Target);

	if (m_IsActive && m_IsMovable) {

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
			vDirection += +XMVectorSet(0.0f,1.0f,0.0f,0.0f);
		}
		if (KeyLogger_Press(KL_FALL)) {
			vDirection += -XMVectorSet(0.0f,1.0f,0.0f,0.0f);
		}

		if (KeyLogger_Press(KL_TURN_LEFT)) {
			XMMATRIX mtxR = XMMatrixRotationY(-m_RoutationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vRight = XMVector3TransformNormal(vRight, mtxR);
			vUp = XMVector3Cross(vForward, vRight);
		}
		if (KeyLogger_Press(KL_TURN_RIGHT)) {
			XMMATRIX mtxR = XMMatrixRotationY(m_RoutationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vRight = XMVector3TransformNormal(vRight, mtxR);
			vUp = XMVector3Cross(vForward, vRight);
		}
		if (KeyLogger_Press(KL_TURN_UP)) {
			XMMATRIX mtxR = XMMatrixRotationAxis(-vRight, m_RoutationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vUp = XMVector3TransformNormal(vUp, mtxR);
		}
		if (KeyLogger_Press(KL_TURN_DOWN)) {
			XMMATRIX mtxR = XMMatrixRotationAxis(vRight, m_RoutationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vUp = XMVector3TransformNormal(vUp, mtxR);
		}
		vPosition += vDirection * m_CameraSpeedFirst;
		float len;  
		XMStoreFloat(&len, XMVector3Length(vDirection));
		if ( len == 0.0f) {
			m_MoveSpeed = 0.0f;
		}
		else
		{
			m_MoveSpeed = m_CameraSpeedFirst;
		}
	}
	else if(m_IsActive && !m_IsMovable) {
		Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
		/*XMVECTOR pFront = XMLoadFloat3(player->GetFront());
		vForward = pFront;*/
		if (!player) return;
		XMVECTOR vDiffCtoP, vLengthCtoP, vPlayerPositon;
		vPlayerPositon = XMLoadFloat3(&player->GetPosition());
		vDiffCtoP = vPlayerPositon - vPosition;
		vLengthCtoP = XMVector3Length(vDiffCtoP);
		float length;
		XMStoreFloat(&length, vLengthCtoP);


		if (Input::GetMouseActive())
		{
			if (JudgeActiveWindow())
			{
				float mouseRot = m_RoutationalSpeed * 0.5f;
				ShowCursor(false);
				if (Input::GetMouseVelocity().x >= 1.0f)
				{
					XMMATRIX mtxR = XMMatrixRotationY(mouseRot);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vForward = XMVector3Normalize(vForward);
					vRight = XMVector3Normalize(vRight);
					vRight = XMVector3TransformNormal(vRight, mtxR);
					vUp = XMVector3Cross(vForward, vRight);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				if (Input::GetMouseVelocity().x <= -1.0f)
				{
					XMMATRIX mtxR = XMMatrixRotationY(-mouseRot);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vRight = XMVector3TransformNormal(vRight, mtxR);
					vForward = XMVector3Normalize(vForward);
					vRight = XMVector3Normalize(vRight);
					vUp = XMVector3Cross(vForward, vRight);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				if (Input::GetMouseVelocity().y >= 1.0f)
				{
					XMMATRIX mtxR = XMMatrixRotationAxis(vRight, mouseRot / 4);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vForward = XMVector3Normalize(vForward);
					vUp = XMVector3TransformNormal(vUp, mtxR);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				if (Input::GetMouseVelocity().y <= -1.0f)
				{
					XMMATRIX mtxR = XMMatrixRotationAxis(vRight, -mouseRot / 4);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vForward = XMVector3Normalize(vForward);
					vUp = XMVector3TransformNormal(vUp, mtxR);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				vAt = XMLoadFloat3(&player->GetPosition());
				SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			}
			else
			{
				ShowCursor(true);
			}
		}
		else
		{
			ShowCursor(true);
			if (!m_IsLock)
			{
				if (KeyLogger_Press(KL_TURN_RIGHT))
				{
					XMMATRIX mtxR = XMMatrixRotationY(m_RoutationalSpeed / 2);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vForward = XMVector3Normalize(vForward);
					vRight = XMVector3Normalize(vRight);
					vRight = XMVector3TransformNormal(vRight, mtxR);
					vUp = XMVector3Cross(vForward, vRight);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				if (KeyLogger_Press(KL_TURN_LEFT))
				{
					XMMATRIX mtxR = XMMatrixRotationY(-m_RoutationalSpeed / 2);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vRight = XMVector3TransformNormal(vRight, mtxR);
					vForward = XMVector3Normalize(vForward);
					vRight = XMVector3Normalize(vRight);
					vUp = XMVector3Cross(vForward, vRight);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				if (KeyLogger_Press(KL_TURN_UP))
				{
					XMMATRIX mtxR = XMMatrixRotationAxis(vRight, m_RoutationalSpeed / 4 / 2);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vForward = XMVector3Normalize(vForward);
					vUp = XMVector3TransformNormal(vUp, mtxR);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				if (KeyLogger_Press(KL_TURN_DOWN))
				{
					XMMATRIX mtxR = XMMatrixRotationAxis(vRight, -m_RoutationalSpeed / 4 / 2);
					vForward = XMVector3TransformNormal(vForward, mtxR);
					vForward = XMVector3Normalize(vForward);
					vUp = XMVector3TransformNormal(vUp, mtxR);
					vPosition = vPlayerPositon + (-vForward * length);
				}
				vAt = XMLoadFloat3(&player->GetPosition());
			}
		}
		vDirection += XMLoadFloat3(&player->GetMove());
		// プレイヤーを追いかける
		vPosition += vDirection;

		float len;
		XMStoreFloat(&len, XMVector3Length(vDirection));
		if (len == 0.0f) {
			m_MoveSpeed = 0.0f;
		}
		else
		{
			m_MoveSpeed = player->GetSpeed();
		}


	}
	else {
		// カメラが動かせない状態
	}


	// 移動
	//	vPosition += vDirection * m_MoveSpeed;
	// 注視点計算
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player) return;
	if (m_IsLock) {
		vAt = XMLoadFloat3(m_LockTargetPos);
		XMVECTOR vPlayerPos = XMLoadFloat3(&player->GetPosition());
		XMVECTOR diffPos =  vPlayerPos - XMLoadFloat3(m_LockTargetPos);
		diffPos = XMVector3Normalize(diffPos);
		diffPos.m128_f32[1] = 0.0f;
		vPosition = vPlayerPos + diffPos * 5.0f;
		vPosition.m128_f32[1] += 3.0f;

		vForward = - diffPos;
		//	vForward.m128_f32[1] = 0.0f;
		vUp = XMLoadFloat3(&m_Direction.Up);
		vRight = XMVector3Cross(vUp, vForward);
		XMStoreFloat3(&m_Direction.Forward, vForward);
		XMStoreFloat3(&m_Direction.Right, vRight);
		XMStoreFloat3(&m_Direction.Up, vUp);

	}
	else
	{
		vAt = XMLoadFloat3(&player->GetPosition());
	}

	// 変数保存
	XMStoreFloat3(&m_Target, vAt);
	XMStoreFloat3(&m_Position, vPosition);
	XMStoreFloat3(&m_Direction.Forward, vForward);
	XMStoreFloat3(&m_Direction.Right, vRight);
	XMStoreFloat3(&m_Direction.Up, vUp);
	XMStoreFloat3(&m_Move, vDirection);

}

void Camera::Draw()
{
	if (!m_IsActive) return;
	// ビューマトリクス設定
	XMStoreFloat4x4(&m_ViewMatrix , XMMatrixLookAtLH(XMLoadFloat3(&m_Position), XMLoadFloat3(&m_Target), XMLoadFloat3(&m_Direction.Up)));
	Renderer::SetViewMatrixX(&m_ViewMatrix);

	//D3DXMATRIX viewMatrix;
	//D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f,1.0f,0.0f));
	//Renderer::SetViewMatrix(&viewMatrix);

	// プロジェクションマトリクス設定
	float fov = 1.0f; //XMConvertToRadians(45.0f);
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float nearZ = 0.01f;
	float farZ = 1000.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);
	XMStoreFloat4x4(&m_ProjectionMatrix, projMatrix);
	Renderer::SetProjectionMatrixX(&m_ProjectionMatrix);

	Renderer::SetCameraPosition(m_Position);

	/*D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(&projectionMatrix);*/
}

bool Camera::CheckView(XMFLOAT3 pos, XMFLOAT3 scale)
{
	// 視錘台カリング
	XMMATRIX view = XMLoadFloat4x4(&m_ViewMatrix);

	XMMATRIX vp, invvp;
	vp = XMLoadFloat4x4(&m_ViewMatrix) * XMLoadFloat4x4(&m_ProjectionMatrix);
	invvp =	XMMatrixInverse(nullptr, vp);
	XMFLOAT3 vpos[4];
	XMVECTOR vVpos[4];
	XMVECTOR vWpos[4];
	float dot;
	XMFLOAT3 fixPos, fixScale;
	//	fixScale = XMFLOAT3(scale.x * 0.5f, scale.y * 0.5f, scale.z * 0.5f);
	fixScale = scale;
	fixPos = pos;

	vpos[0] = XMFLOAT3(-1.0f, +1.0f, 1.0f);
	vpos[1] = XMFLOAT3(+1.0f, +1.0f, 1.0f);
	vpos[2] = XMFLOAT3(-1.0f, -1.0f, 1.0f);
	vpos[3] = XMFLOAT3(+1.0f, -1.0f, 1.0f);

	for (int i = 0; i < 4;i++)
	{
		vVpos[i] = XMLoadFloat3(&vpos[i]);
		vWpos[i] = XMVector3TransformCoord(vVpos[i], invvp);
	}

	XMVECTOR v, v1, v2, vn, vCameraPosition;
	vCameraPosition = XMLoadFloat3(&m_Position);
	v = XMLoadFloat3(&fixPos) - vCameraPosition;

	// 左面
	fixPos = pos;
	fixPos.x += fixScale.x;
	v = XMLoadFloat3(&fixPos) - vCameraPosition;
	v1 = vWpos[0] - vCameraPosition;
	v2 = vWpos[2] - vCameraPosition;
	vn =  XMVector3Cross(v1, v2);

	XMStoreFloat(&dot, XMVector3Dot(vn, v));
	if (dot < 0.0f)
	{
		return false;
	}

	// 右面
	fixPos = pos;
	fixPos.x -= fixScale.x;
	v = XMLoadFloat3(&fixPos) - vCameraPosition;
	v1 = vWpos[3] - vCameraPosition;
	v2 = vWpos[1] - vCameraPosition;
	vn =  XMVector3Cross(v1, v2);
	XMStoreFloat(&dot, XMVector3Dot(vn, v));
	if (dot < 0.0f)
	{
		return false;
	}

	// 上面
	fixPos = pos;
	fixPos.y -= fixScale.x;
	v = XMLoadFloat3(&fixPos) - vCameraPosition;
	v1 = vWpos[1] - vCameraPosition;
	v2 = vWpos[0] - vCameraPosition;
	vn =  XMVector3Cross(v1, v2);
	XMStoreFloat(&dot, XMVector3Dot(vn, v));
	if (dot < 0.0f)
	{
		return false;
	}

	// 下面
	fixPos = pos;
	fixPos.y += fixScale.x;
	v = XMLoadFloat3(&fixPos) - vCameraPosition;
	v1 = vWpos[2] - vCameraPosition;
	v2 = vWpos[3] - vCameraPosition;
	vn =  XMVector3Cross(v1, v2);
	XMStoreFloat(&dot, XMVector3Dot(vn, v));
	if (dot < 0.0f)
	{
		return false;
	}


	return true;
}

float Camera::GetSpeed()
{
	return m_MoveSpeed;
}

void Camera::ChangeMovableWithPlayer()
{
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player)return;
	if (!m_IsMovable)
	{
		m_IsMovable = true;
		player->SetMovable(false);
	}
	else
	{
		m_IsMovable = false;
		player->SetMovable(true);
	}
}

void Camera::ChangeMovableWithPlayer(bool movable)
{
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player)return;
	m_IsMovable = movable;
	player->SetMovable(!movable);
}

void  Camera::ChangeDir(float angle, bool isRight) {

	XMVECTOR vPositon = XMLoadFloat3(&m_Position);

	XMVECTOR vForward = XMLoadFloat3(&m_Direction.Forward);
	XMVector3Normalize(vForward);
	XMVECTOR vRight = XMLoadFloat3(&m_Direction.Right);
	XMVector3Normalize(vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_Direction.Up);
	XMVector3Normalize(vUp);	

	XMVECTOR vAt = vPositon + vForward * m_AtLength;


	XMMATRIX mtxR = XMMatrixRotationY(angle);
	vForward = XMVector3TransformNormal(vForward, mtxR);
	vRight = XMVector3TransformNormal(vRight, mtxR);
	vUp = XMVector3Cross(vForward, vRight);

	vPositon = XMLoadFloat3(&m_Target) - vForward * m_AtLength;

	isRight = isRight;
	// if(isRight){
	// XMMATRIX mtxR = XMMatrixRotationY(angle);
	// 		vForward = XMVector3TransformNormal(vForward, mtxR);
	// 		vRight = XMVector3TransformNormal(vRight, mtxR);
	// 		vUp = XMVector3Cross(vForward, vRight);
	// }
	// else{
	// XMMATRIX mtxR = XMMatrixRotationY(angle);
	// 		vForward = XMVector3TransformNormal(vForward, mtxR);
	// 		vRight = XMVector3TransformNormal(vRight, mtxR);
	// 		vUp = XMVector3Cross(vForward, vRight);
	// }


	XMStoreFloat3(&m_Direction.Forward, vForward);
	XMStoreFloat3(&m_Direction.Right, vRight);
	XMStoreFloat3(&m_Direction.Up, vUp);
	XMStoreFloat3(&m_Position, vPositon);
}

