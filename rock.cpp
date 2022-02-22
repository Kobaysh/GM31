#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "camera.h"
#include "meshField.h"
#include "player.h"
#include "obb.h"
#include "rock.h"

ID3D11VertexShader* Rock::m_VertexShader = nullptr;
ID3D11PixelShader* Rock::m_PixelShader = nullptr;
ID3D11InputLayout* Rock::m_VertexLayout = nullptr;


void Rock::Init()
{

//	m_model->Load("asset\\model\\torus\\torus.obj"); // \\か//しか使えない
//	m_model->Load("asset\\model\\bricktorus\\bricktorus.obj");	 // \\か//しか使えない
//	m_model->Load("asset\\model\\test\\DX.obj");	 // \\か//しか使えない
//	m_model->Load("asset\\model\\rock\\rock.obj");	 // \\か//しか使えない
	m_ModelId = Model::SetModelLoadfile("asset\\model\\rock\\rock.obj");
	Model::Load(m_ModelId);
//	Model::AllLoad();
	m_Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(3.0f, 3.0f, 3.0f);
	m_Front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	
	if (!m_Obb)
	{
		m_Obb = new OBB(m_Position, XMFLOAT3(3.0f, 3.0f, 3.0f));
	//	ManagerT::GetScene()->AddGameObject(m_Obb, GOT_OBJECT3D);
	}
	if (!m_VertexShader) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/vertexLightingVS.cso");
	}
	if (!m_PixelShader) {
		Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/vertexLightingPS.cso");
	}
}

void Rock::Init(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
{
	m_ModelId = Model::SetModelLoadfile("asset\\model\\rock\\rock.obj");
		Model::Load(m_ModelId);
	//Model::AllLoad();
	m_Position = pos;
	m_Rotation = rot;
	m_Scale = scale;
	m_Front = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3 fixedScale = m_Scale;
	fixedScale.x *= 2;
	fixedScale.y *= 2;
	fixedScale.z *= 2;
	if (!m_Obb)
	{
		m_Obb = new OBB(m_Position, m_Rotation, fixedScale);
	//	ManagerT::GetScene()->AddGameObject(m_Obb, GOT_OBJECT3D);
	}
	else
	{
		m_Obb->SetPosition(m_Position);
		m_Obb->SetRotation(m_Rotation);
		m_Obb->SetScale(fixedScale);
	}
	if (!m_VertexShader) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/vertexLightingVS.cso");
	}
	if (!m_PixelShader) {
		Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/vertexLightingPS.cso");
	}
}

void Rock::Uninit()
{
	//m_model->Unload();
	//delete m_model;
	if (m_Obb)
	{
	//	m_Obb->SetDead();
		delete m_Obb;
		m_Obb = nullptr;
	}
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
	//if (m_Obb) {
	//	m_Obb->SetDead();
	//}
}

void Rock::Update()
{
	Scene* scene = ManagerT::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(GOT_OBJECT3D);
	m_Position.y = meshField->GetHeight(m_Position) + m_Scale.y / 2;
	//Player* player = scene->GetGameObject<Player>(GOT_OBJECT3D);
	//if (OBB::ColOBBs(GetObb(), player->GetObb()))
	//{
	//	int a = 0;
	//}
}

void Rock::Draw()
{
	// 視錘台カリング
	Scene* scene = ManagerT::GetScene();
	Camera* camera = scene->GetGameObject<Camera>(GOT_CAMERA);
	XMFLOAT3 fixedScale = m_Scale;
	fixedScale.x *= 1.0f;
	fixedScale.y *= 1.0f;
	fixedScale.z *= 1.0f;
	if (!camera->CheckView(m_Position, fixedScale))
	{
		return;
	}
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_Front.z, m_Front.x));
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX* rotX *transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	Model::Draw(m_ModelId);
	//m_model->Draw();
//	m_Obb->Draw();
}