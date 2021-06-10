#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "enemy.h"
#include "bullet.h"

#define FILENAME ("asset\\model\\bullet\\kidantorus.obj")

Bullet::Bullet()
{
	m_Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_speed = 0.0f;
}

Bullet::Bullet(XMFLOAT3 f3Position)
{
	m_Position = f3Position;
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_speed = 0.0f;
}

void Bullet::Init()
{
	m_model = new Model();
	m_model->Load(FILENAME);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Bullet::Uninit()
{
	m_model->Unload();
	delete m_model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Update()
{
	XMVECTOR vPosition = XMLoadFloat3(&m_Position);
	XMVECTOR vDirection = XMLoadFloat3(&m_direction);
	vPosition += vDirection * m_speed;
	XMStoreFloat3(&m_Position, vPosition);

	if (m_Position.z > 10.0f) {
		SetDead();
		return;
	}

	// Enemyとの当たり判定

	Scene* scene = ManagerT::GetScene();
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>();
	for (Enemy* enemy : enemies) {
		XMFLOAT3 enemyPosition = enemy->GetPosition();
		XMVECTOR direction;
		direction = XMLoadFloat3(&m_Position) - XMLoadFloat3(&enemyPosition);
		XMVECTOR length =  XMVector3Length(direction);
		float distance = 0.0f;
		XMStoreFloat(&distance, length);
		if (distance < 2.0f) {
			enemy->SetDead();
			SetDead();
		}
	}
}

void Bullet::Draw()
{
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);


	m_model->Draw();
}

Bullet * Bullet::Create(XMFLOAT3 f3Position, XMFLOAT3 f3Direction, float fSpeed)
{
	Bullet* pBullet = new Bullet();
	ManagerT::GetScene()->AddGameObject(pBullet, GameObject::GOT_OBJECT3D);
//	Bullet* pBullet =  ManagerT::GetScene()->AppendGameObject<Bullet>();
	pBullet->SetPosition(f3Position);
	pBullet->m_direction = f3Direction;
	pBullet->m_speed = fSpeed;
	return pBullet;
}

void Bullet::Destroy(Bullet * pBullet)
{
	delete pBullet;
	pBullet = NULL;
}
