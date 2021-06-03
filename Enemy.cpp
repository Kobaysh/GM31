#include "main.h"
#include "renderer.h"
#include "model.h"
#include "enemy.h"

#define FILENAME ("asset\\model\\enemy\\brickcube.obj")

void Enemy::Init()
{
	m_model = new Model();
	m_model->Load(FILENAME);
	m_Position = XMFLOAT3(2.0f, 1.0f, 1.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	
}

void Enemy::Uninit()
{
	m_model->Unload();
	delete m_model;
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Enemy::Update()
{
	m_Rotation.y += 0.01f;
	m_Rotation.z += 0.01f;
}

void Enemy::Draw()
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
