#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "keylogger.h"
#include "manager.h"
#include "scene.h"
#include "obb.h"
#include "player.h"
#include "input.h"


float Camera::m_routationalSpeed;

const  float Camera::m_cameraSpeedFirst = 0.2f;
const  float Camera::m_atLength = 1.0f;




void Camera::Init()
{
	m_position	 = XMFLOAT3(0.0f, 4.0f, -10.0f);
	m_target	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_direction.m_forward	 = XMFLOAT3(0.0f, -0.3f, 1.0f);
	m_direction.m_right		 = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_direction.m_up		 = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_routationalSpeed = 0.08f;
	m_moveSpeed = m_cameraSpeedFirst;
	m_isActive = true;
}

void Camera::Init(bool active, bool movable)
{
	m_position	 = XMFLOAT3(0.0f, 4.0f, -10.0f);
	m_target	 = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_direction.m_forward	 = XMFLOAT3(0.0f, -0.3f, 1.0f);
	m_direction.m_right		 = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_direction.m_up		 = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_routationalSpeed = 0.08f;
	m_moveSpeed = m_cameraSpeedFirst;
	m_isActive = active;
	m_movable = movable;
}

void Camera::Uninit()
{
}

void Camera::Update()
{

	
	//if (KeyLogger_Trigger(KL_GUARD))
	//{
	//	ChangeMovableWithPlayer(!m_movable);
	//}

	
	// 変数用意
	XMVECTOR vDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMStoreFloat3(&m_move, vDirection);
	XMVECTOR vPosition = XMLoadFloat3(&m_position);
	XMVECTOR vForward = XMLoadFloat3(&m_direction.m_forward);
	XMVector3Normalize(vForward);
	XMVECTOR vRight = XMLoadFloat3(&m_direction.m_right);
	XMVector3Normalize(vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_direction.m_up);
	XMVector3Normalize(vUp);
	XMFLOAT3 tempFront = m_direction.m_forward;
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
			vDirection += +XMVectorSet(0.0f,1.0f,0.0f,0.0f);
		}
		if (KeyLogger_Press(KL_FALL)) {
			vDirection += -XMVectorSet(0.0f,1.0f,0.0f,0.0f);
		}

		if (KeyLogger_Press(KL_TURN_LEFT)) {
			XMMATRIX mtxR = XMMatrixRotationY(-m_routationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vRight = XMVector3TransformNormal(vRight, mtxR);
			vUp = XMVector3Cross(vForward, vRight);
		}
		if (KeyLogger_Press(KL_TURN_RIGHT)) {
			XMMATRIX mtxR = XMMatrixRotationY(m_routationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vRight = XMVector3TransformNormal(vRight, mtxR);
			vUp = XMVector3Cross(vForward, vRight);
		}
		if (KeyLogger_Press(KL_TURN_UP)) {
			XMMATRIX mtxR = XMMatrixRotationAxis(-vRight, m_routationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vUp = XMVector3TransformNormal(vUp, mtxR);
		}
		if (KeyLogger_Press(KL_TURN_DOWN)) {
			XMMATRIX mtxR = XMMatrixRotationAxis(vRight, m_routationalSpeed);
			vForward = XMVector3TransformNormal(vForward, mtxR);
			vUp = XMVector3TransformNormal(vUp, mtxR);
		}
		vPosition += vDirection * m_cameraSpeedFirst;
		float len;  
		XMStoreFloat(&len, XMVector3Length(vDirection));
		if ( len == 0.0f) {
			m_moveSpeed = 0.0f;
		}
		else
		{
			m_moveSpeed = m_cameraSpeedFirst;
		}
	}
	else if(m_isActive && !m_movable) {
		Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
		/*XMVECTOR pFront = XMLoadFloat3(player->GetFront());
		vForward = pFront;*/

		XMVECTOR vDiffCtoP, vLengthCtoP, vPlayerPositon;
		vPlayerPositon = XMLoadFloat3(&player->GetPosition());
		vDiffCtoP = vPlayerPositon - vPosition;
		vLengthCtoP = XMVector3Length(vDiffCtoP);
		float length;
		XMStoreFloat(&length, vLengthCtoP);

#if MOUSE_TRUE
		if (JudgeActiveWindow()) {
//		if (false) {
			
		//	ShowCursor(false);
			if (Input::GetMouseVelocity().x >= 1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationY(m_routationalSpeed);
				vForward = XMVector3TransformNormal(vForward, mtxR);
				vForward = XMVector3Normalize(vForward);
				vRight = XMVector3Normalize(vRight);
				vRight = XMVector3TransformNormal(vRight, mtxR);
				vUp = XMVector3Cross(vForward, vRight);
				vPosition = vPlayerPositon + (-vForward * length);
			}
			if (Input::GetMouseVelocity().x <= -1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationY(-m_routationalSpeed);
				vForward = XMVector3TransformNormal(vForward, mtxR);
				vRight = XMVector3TransformNormal(vRight, mtxR);
				vForward = XMVector3Normalize(vForward);
				vRight = XMVector3Normalize(vRight);
				vUp = XMVector3Cross(vForward, vRight);
				vPosition = vPlayerPositon + (-vForward * length);
			}
			if (Input::GetMouseVelocity().y >= 1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationAxis(vRight, m_routationalSpeed / 4);
				vForward = XMVector3TransformNormal(vForward, mtxR);
				vForward = XMVector3Normalize(vForward);
				vUp = XMVector3TransformNormal(vUp, mtxR);
				vPosition = vPlayerPositon + (-vForward * length);
			}
			if (Input::GetMouseVelocity().y <= -1.0f)
			{
				XMMATRIX mtxR = XMMatrixRotationAxis(vRight, -m_routationalSpeed / 4);
				vForward = XMVector3TransformNormal(vForward, mtxR);
				vForward = XMVector3Normalize(vForward);
				vUp = XMVector3TransformNormal(vUp, mtxR);
				vPosition = vPlayerPositon + (-vForward * length);
			}
			vAt = XMLoadFloat3(&player->GetPosition());
	
		}
		else {
			ShowCursor(true);
		}
#endif
		vDirection += XMLoadFloat3(&player->GetMove());
		// プレイヤーを追いかける
		vPosition += vDirection;

		float len;
		XMStoreFloat(&len, XMVector3Length(vDirection));
		if (len == 0.0f) {
			m_moveSpeed = 0.0f;
		}
		else
		{
			m_moveSpeed = player->GetSpeed();
		}


	}
	else {
		// カメラが動かせない状態
	}

#if MOUSE_TRUE

#else

	// 移動
//	vPosition += vDirection * m_moveSpeed;
	// 注視点計算

	vAt = vPosition + vForward * m_atLength;
#endif
	// 変数保存
	XMStoreFloat3(&m_target, vAt);
	XMStoreFloat3(&m_position, vPosition);
	XMStoreFloat3(&m_direction.m_forward, vForward);
	XMStoreFloat3(&m_direction.m_right, vRight);
	XMStoreFloat3(&m_direction.m_up, vUp);
	XMStoreFloat3(&m_move, vDirection);

}

void Camera::Draw()
{
	if (!m_isActive) return;
	// ビューマトリクス設定
	XMStoreFloat4x4(&m_viewMatrix , XMMatrixLookAtLH(XMLoadFloat3(&m_position), XMLoadFloat3(&m_target), XMLoadFloat3(&m_direction.m_up)));
	Renderer::SetViewMatrixX(&m_viewMatrix);
	
	//D3DXMATRIX viewMatrix;
	//D3DXMatrixLookAtLH(&viewMatrix, &m_position, &m_target, &D3DXVECTOR3(0.0f,1.0f,0.0f));
	//Renderer::SetViewMatrix(&viewMatrix);

	// プロジェクションマトリクス設定
	float fov = 1.0f; //XMConvertToRadians(45.0f);
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float nearZ = 0.01f;
	float farZ = 1000.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);
	XMStoreFloat4x4(&m_projectionMatrix, projMatrix);
	Renderer::SetProjectionMatrixX(&m_projectionMatrix);

	Renderer::SetCameraPosition(m_position);

	/*D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(&projectionMatrix);*/
}

bool Camera::CheckView(XMFLOAT3 pos, XMFLOAT3 scale)
{
	// 視錘台カリング
	XMMATRIX view = XMLoadFloat4x4(&m_viewMatrix);
	
	XMMATRIX vp, invvp;
	vp = XMLoadFloat4x4(&m_viewMatrix) * XMLoadFloat4x4(&m_projectionMatrix);
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
	vCameraPosition = XMLoadFloat3(&m_position);
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
	return m_moveSpeed;
}

void Camera::ChangeMovableWithPlayer()
{
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!m_movable)
	{
		m_movable = true;
		player->SetMovable(false);
	}
	else
	{
		m_movable = false;
		player->SetMovable(true);
	}
}

void Camera::ChangeMovableWithPlayer(bool movable)
{
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	m_movable = movable;
	player->SetMovable(!movable);
}

void  Camera::ChangeDir(float angle, bool isRight) {

	XMVECTOR vPositon = XMLoadFloat3(&m_position);
	
	XMVECTOR vForward = XMLoadFloat3(&m_direction.m_forward);
	XMVector3Normalize(vForward);
	XMVECTOR vRight = XMLoadFloat3(&m_direction.m_right);
	XMVector3Normalize(vRight);
	XMVECTOR vUp = XMLoadFloat3(&m_direction.m_up);
	XMVector3Normalize(vUp);	

	XMVECTOR vAt = vPositon + vForward * m_atLength;


	XMMATRIX mtxR = XMMatrixRotationY(angle);
	vForward = XMVector3TransformNormal(vForward, mtxR);
	vRight = XMVector3TransformNormal(vRight, mtxR);
	vUp = XMVector3Cross(vForward, vRight);
	
	vPositon = XMLoadFloat3(&m_target) - vForward * m_atLength;

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
	

	XMStoreFloat3(&m_direction.m_forward, vForward);
	XMStoreFloat3(&m_direction.m_right, vRight);
	XMStoreFloat3(&m_direction.m_up, vUp);
	XMStoreFloat3(&m_position, vPositon);
}

