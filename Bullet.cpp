#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "model.h"
#include "obb.h"
#include "enemy.h"
#include "bullet.h"
#include "rock.h"
#include "explosion.h"

#define FILENAME ("asset\\model\\bullet\\kidantorus.obj")

#define	BULLET_MAX_RECT (100.0f)

int Bullet::ms_modelId = INVALID_MODEL_ID;
ID3D11VertexShader*		Bullet::m_VertexShader = nullptr;
ID3D11PixelShader*		Bullet::m_PixelShader = nullptr;
ID3D11InputLayout*		Bullet::m_VertexLayout = nullptr;


Bullet::Bullet()
{
	m_Position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.3f, 0.3f, 0.3f);
	m_direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_speed = 0.0f;
	m_obb = new OBB(m_Position, m_Scale);
}

Bullet::Bullet(XMFLOAT3 f3Position)
{
	m_Position = f3Position;
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_speed = 0.0f;
	m_obb = new OBB(m_Position, m_Scale);
}

void Bullet::Init()
{
	/*m_model = new Model();
	m_model->Load(FILENAME);*/
	/*ms_modelId = Model::SetModelLoadfile(FILENAME);
	Model::AllLoad();*/
	if (!m_VertexShader) {

		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	}
	if (!m_PixelShader) {
		if (ms_IsVoidPS) {
			Renderer::CreatePixelShader(&m_PixelShader, "LightingVoidPS.cso");
		}
		else
		{
			Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
		}
	}
//	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}

void Bullet::Uninit()
{
	/*if (m_model) {
		m_model->Unload();
		delete m_model;
		m_model = NULL;
	}*/
	// m_VertexLayout->Release();
	// m_VertexShader->Release();
	// m_PixelShader->Release();
	if (m_obb) {
		delete m_obb;
		m_obb = nullptr;
	}
}

void Bullet::Update()
{
	Scene* scene = ManagerT::GetScene();

	XMVECTOR vPosition = XMLoadFloat3(&m_Position);
	XMVECTOR vDirection = XMLoadFloat3(&m_direction);
	vPosition += vDirection * m_speed;
	XMStoreFloat3(&m_Position, vPosition);

	if (m_Position.z > BULLET_MAX_RECT || m_Position.z < -BULLET_MAX_RECT ||
		m_Position.x > BULLET_MAX_RECT || m_Position.x < -BULLET_MAX_RECT) {
		SetDead();
		// 爆発エフェクト
		scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_Position);
		return;
	}

	// Enemyとの当たり判定

	
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>(GOT_OBJECT3D);

	for (Enemy* enemy : enemies) {
		float distance = 0.0f;
		XMStoreFloat(&distance, XMVector3Length(XMLoadFloat3(&m_Position) - XMLoadFloat3(&enemy->GetPosition())));
		if (distance < 2.0f) {
			enemy->SetDead();
			SetDead();
			// 爆発エフェクト
			scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_Position);
		}
	}

	// rockとの当たり判定

	std::vector<Rock*> rocks = scene->GetGameObjects<Rock>(GOT_OBJECT3D);

	for (Rock* rock : rocks) {
		if (OBB::ColOBBs(*m_obb, rock->GetObb())){
			SetDead();
			scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_Position);
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


//	m_model->Draw();
	Model::Draw(ms_modelId);
}

void Bullet::Load()
{
	ms_modelId = Model::SetModelLoadfile(FILENAME);
//	Model::AllLoad();
	Model::Load(ms_modelId);
}

void Bullet::UnLoad()
{
	Model::Release(ms_modelId);
	if (m_VertexLayout) {
		m_VertexLayout->Release();
		m_VertexLayout = nullptr;
	}
	if (m_VertexShader) {
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
	if (m_PixelShader) {
			m_PixelShader->Release();
			m_PixelShader = nullptr;
	}
}

Bullet * Bullet::Create(XMFLOAT3 f3Position, XMFLOAT3 f3Direction, float fSpeed)
{
//	Bullet* pBullet = new Bullet();
//	ManagerT::GetScene()->AddGameObject(pBullet, GameObject::GOT_OBJECT3D);
	Bullet* pBullet =  ManagerT::GetScene()->AppendGameObject<Bullet>(GameObject::GOT_OBJECT3D);
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
