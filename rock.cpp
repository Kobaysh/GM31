#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "bullet.h"
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

//	m_Model->Load("asset\\model\\torus\\torus.obj"); // \\か//しか使えない
//	m_Model->Load("asset\\model\\bricktorus\\bricktorus.obj");	 // \\か//しか使えない
//	m_Model->Load("asset\\model\\test\\DX.obj");	 // \\か//しか使えない
//	m_Model->Load("asset\\model\\rock\\rock.obj");	 // \\か//しか使えない
	m_modelId = Model::SetModelLoadfile("asset\\model\\rock\\rock.obj");
	Model::Load(m_modelId);
//	Model::AllLoad();
	m_position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale		= XMFLOAT3(3.0f, 3.0f, 3.0f);
	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	
	if (!m_obb)
	{
		m_obb = new OBB(m_position, XMFLOAT3(3.0f, 3.0f, 3.0f));
		ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);
	}
	if (!m_VertexShader) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	}
	if (!m_PixelShader) {
		Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	}
}

void Rock::Init(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale)
{
	m_modelId = Model::SetModelLoadfile("asset\\model\\rock\\rock.obj");
		Model::Load(m_modelId);
	//Model::AllLoad();
	m_position = pos;
	m_rotation = rot;
	m_scale = scale;
	m_front = XMFLOAT3(0.0f, 0.0f, 1.0f);

	XMFLOAT3 fixedScale = m_scale;
	fixedScale.x *= 2;
	fixedScale.y *= 2;
	fixedScale.z *= 2;
	if (!m_obb)
	{
		m_obb = new OBB(m_position, m_rotation, fixedScale);
		ManagerT::GetScene()->AddGameObject(m_obb, GOT_OBJECT3D);
	}
	else
	{
		m_obb->SetPosition(m_position);
		m_obb->SetRotation(m_rotation);
		m_obb->SetScale(fixedScale);
	}
	if (!m_VertexShader) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	}
	if (!m_PixelShader) {
		Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	}
}

void Rock::Uninit()
{
	//m_Model->Unload();
	//delete m_Model;
	SetDead();

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
	//if (m_obb) {
	//	m_obb->SetDead();
	//}
}

void Rock::Update()
{
	Scene* scene = ManagerT::GetScene();
	MeshField* meshField = scene->GetGameObject<MeshField>(GOT_OBJECT3D);
	m_position.y = meshField->GetHeight(m_position) + m_scale.y / 2;
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
	if (!camera->CheckView(m_position, m_scale))
	{
		return;
	}
	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
//	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_front.z, m_front.x));
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX* rotX *transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	Model::Draw(m_modelId);
	//m_Model->Draw();
//	m_obb->Draw();
}