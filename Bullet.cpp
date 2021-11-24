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
	m_position = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(0.3f, 0.3f, 0.3f);
	m_direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_speed = 0.0f;
	m_obb = new OBB(m_position, XMFLOAT3(1.0f,0.5f,1.0f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);
}

Bullet::Bullet(XMFLOAT3 f3Position)
{
	m_position = f3Position;
	m_rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(0.1f, 0.1f, 0.1f);
	m_direction = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_speed = 0.0f;
	m_obb = new OBB(m_position, XMFLOAT3(1.0f,0.5f,1.0f));
	ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);
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
		m_obb->SetDead();
		/*delete m_obb;
		m_obb = nullptr;*/
	}
}

void Bullet::Update()
{
	Scene* scene = ManagerT::GetScene();

	XMVECTOR vPosition = XMLoadFloat3(&m_position);
	XMVECTOR vDirection = XMLoadFloat3(&m_direction);
	vPosition += vDirection * m_speed;
	XMStoreFloat3(&m_position, vPosition);
	m_obb->SetPosition(m_position);

	if (m_position.z > BULLET_MAX_RECT || m_position.z < -BULLET_MAX_RECT ||
		m_position.x > BULLET_MAX_RECT || m_position.x < -BULLET_MAX_RECT) {
		SetDead();
		// 爆発エフェクト
		scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_position);
		return;
	}

	// Enemyとの当たり判定

	
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>(GOT_OBJECT3D);

	for (Enemy* enemy : enemies) {
		//float distance = 0.0f;
		//XMStoreFloat(&distance, XMVector3Length(XMLoadFloat3(&m_position) - XMLoadFloat3(&enemy->GetPosition())));
		//if (distance < 2.0f) {
		//	enemy->SetDead();
		//	SetDead();
		//	// 爆発エフェクト
		//	scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_position);
		//}

		if (OBB::ColOBBs(*m_obb, enemy->GetObb()))
		{
			SetDead();
			// 爆発エフェクト
			scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_position);
		}
		//float distance = 0.0f;
		//
		//XMStoreFloat(&distance, XMVector3Length(XMLoadFloat3(&m_position) - XMLoadFloat3(&enemy->GetPosition())));
		//if (distance < 2.0f) {
		////	enemy->SetDead();
		//	SetDead();
		//	// 爆発エフェクト
		//	scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_position);
		//}
	}

	// rockとの当たり判定

	std::vector<Rock*> rocks = scene->GetGameObjects<Rock>(GOT_OBJECT3D);

	for (Rock* rock : rocks) {
		if (OBB::ColOBBs(*m_obb, rock->GetObb())){
			SetDead();
			scene->AppendGameObject<Explosion>(GOT_OBJECT3D)->SetPosition(m_position);
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
	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


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
