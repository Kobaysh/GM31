#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "bullet.h"
#include "rock.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)

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
//	Model::Load(m_modelId);
	Model::AllLoad();
	m_Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(3.0f, 3.0f, 3.0f);
	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_speed = MOVE_SPEED;

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


	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Rock::Update()
{

	
}

void Rock::Draw()
{

	// 入力レイアウト設定
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// シェーダー設定
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// マトリクス設定
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	XMMATRIX rotX = XMMatrixRotationY(-atan2f(m_front.z, m_front.x));
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX* rotX *transX;
	Renderer::SetWorldMatrixX(&worldX);

	Model::Draw(m_modelId);
	//m_Model->Draw();
}