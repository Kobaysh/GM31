#include "main.h"
#include "Camera.h"
#include "renderer.h"

void Camera::Init()
{
	m_vPosition = XMVectorSet(0.0f, 2.0f, -5.0f,0.0f);
	m_vTarget = XMVectorSet(0.0f, 0.0f, 0.0f,0.0f);
	m_Position = D3DXVECTOR3(0.0f, 2.0f, -5.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Camera::Uninit()
{
}

void Camera::Update()
{
}

void Camera::Draw()
{
	// ビューマトリクス設定
//	XMMATRIX viewMatrixX;
	D3DXMATRIX viewMatrix;
	D3DXMatrixLookAtLH(&viewMatrix, &m_Position, &m_Target, &D3DXVECTOR3(0.0f,1.0f,0.0f));
//	XMMatrixLookAtLH(m_vPosition, m_vTarget, m_vUp);
	
	Renderer::SetViewMatrix(&viewMatrix);

	// プロジェクションマトリクス設定
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);
	Renderer::SetProjectionMatrix(&projectionMatrix);
	
	/*float fov = XMConvertToRadians(45.0f);
	float aspect = (float)SCREEN_WIDTH / SCREEN_HEIGHT;
	float nearZ = 0.1f;
	float farZ = 1000.0f;
	XMMATRIX projMatrix = XMMatrixPerspectiveFovLH(fov, aspect, nearZ, farZ);*/

}
