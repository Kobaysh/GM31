#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "keylogger.h"
#include "debugCamera.h"

void DebugCamera::Update()
{
	if (!m_isActive) return;
	

	// �ϐ��p��
	XMVECTOR vDirection = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMStoreFloat3(&m_move, vDirection);
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
	
	else {
		// �J�������������Ȃ����
	}

	// �ړ�
	//	vPosition += vDirection * m_moveSpeed;
	// �����_�v�Z

	vAt = vPosition + vForward * m_atLength;
	// �ϐ��ۑ�
	XMStoreFloat3(&m_target, vAt);
	XMStoreFloat3(&m_Position, vPosition);
	XMStoreFloat3(&m_Direction.Forward, vForward);
	XMStoreFloat3(&m_Direction.Right, vRight);
	XMStoreFloat3(&m_Direction.Up, vUp);
	XMStoreFloat3(&m_move, vDirection);


}

void DebugCamera::Draw()
{
	if (!m_isActive) return;
	Camera::Draw();
}
