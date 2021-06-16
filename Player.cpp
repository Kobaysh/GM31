#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "bullet.h"
#include "player.h"

bool GameObject::m_sIsVoidPS = false;

void Player::Init()
{
	m_Model = new Model();
//	m_Model->Load("asset\\model\\torus\\torus.obj"); // \\��//�����g���Ȃ�
	m_Model->Load("asset\\model\\bricktorus\\bricktorus.obj");	 // \\��//�����g���Ȃ�
	

	m_Position	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_speed = 0.1f;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

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

	Move();
	Shoot();
	VoidDimension();
}

void Player::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);


	m_Model->Draw();
}

void Player::Move()
{
	if (ManagerT::GetScene()->GetGameObject<Camera>()->GetIsActive()) return;
	XMVECTOR direction = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR vPositon;
	vPositon = XMLoadFloat3(&m_Position);
	XMFLOAT3 input_direction = { 0.0f,0.0f,0.0f };
	if (KeyLogger_Press(KL_UP)) {
		input_direction.z += 1.0f;
	}
	if (KeyLogger_Press(KL_DOWN)) {
		input_direction.z += -1.0f;
	}
	if (KeyLogger_Press(KL_RIGHT)) {
		input_direction.x += 1.0f;
	}
	if (KeyLogger_Press(KL_LEFT)) {
		input_direction.x += -1.0f;
	}
	direction = XMLoadFloat3(&input_direction);
	XMVector3Normalize(direction);
	vPositon += direction * m_speed;
	XMStoreFloat3(&m_Position, vPositon);
}

void Player::Shoot()
{
	if (KeyLogger_Trigger(KL_FIRE)) {
		Bullet::Create(m_Position, m_front, 0.3f);
	}
}

void Player::VoidDimension()
{
	if (KeyLogger_Trigger(KL_WIRE)) {
		if (m_sIsVoidPS) {
			ManagerT::GetScene()->AllPSChange("vertexLightingPS.cso");
			m_sIsVoidPS = false;
		}
		else
		{
			ManagerT::GetScene()->AllPSChange("LightingVoidPS.cso");
			m_sIsVoidPS = true;
		}
	}
}
