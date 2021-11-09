#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "bullet.h"
#include "obb.h"
#include "rock.h"

ID3D11VertexShader* Rock::m_VertexShader = nullptr;
ID3D11PixelShader* Rock::m_PixelShader = nullptr;
ID3D11InputLayout* Rock::m_VertexLayout = nullptr;


void Rock::Init()
{

//	m_Model->Load("asset\\model\\torus\\torus.obj"); // \\��//�����g���Ȃ�
//	m_Model->Load("asset\\model\\bricktorus\\bricktorus.obj");	 // \\��//�����g���Ȃ�
//	m_Model->Load("asset\\model\\test\\DX.obj");	 // \\��//�����g���Ȃ�
//	m_Model->Load("asset\\model\\rock\\rock.obj");	 // \\��//�����g���Ȃ�
	m_modelId = Model::SetModelLoadfile("asset\\model\\rock\\rock.obj");
//	Model::Load(m_modelId);
	Model::AllLoad();
	m_position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale		= XMFLOAT3(3.0f, 3.0f, 3.0f);
	m_front		= XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_obb = new OBB(m_position, XMFLOAT3(3.0f, 3.0f, 3.0f));

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
	//	Model::Load(m_modelId);
	Model::AllLoad();
	m_position = pos;
	m_rotation = rot;
	m_scale = scale;
	m_front = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_obb = new OBB(m_position, m_scale);

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


	if (m_VertexLayout) {
		m_VertexLayout->Release();
		m_VertexLayout = nullptr;
	}
	if (m_VertexLayout) {
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
	if (m_VertexLayout) {
			m_PixelShader->Release();
			m_PixelShader = nullptr;
	}
	if (m_obb) {
		delete m_obb;
		m_obb = nullptr;
	}
}

void Rock::Update()
{

	
}

void Rock::Draw()
{

	// ���̓��C�A�E�g�ݒ�
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
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
}