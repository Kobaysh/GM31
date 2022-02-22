#include "main.h"

#include "renderer.h"
#include "model.h"
#include "manager.h"
#include "scene.h"
#include "keylogger.h"
#include "obb.h"
#include "camera.h"
#include "player.h"
#include "sky.h"


#define NEARLY_ZERO_VALUE 0.01f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.22f)
#define MOVE_SPEED (0.1f)


void Sky::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\sky\\skydome.obj");	 // \\か//しか使えない
	

	m_Position	= XMFLOAT3(0.0f, -20.0f, 0.0f);
	m_Rotation	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale		= XMFLOAT3(100.0f, 100.0f, 100.0f);
	m_Front		= XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_Speed = MOVE_SPEED;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/unlitTexturePS.cso");

}

void Sky::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Sky::Update()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	XMVECTOR vPos = XMLoadFloat3(&m_Position);
	// カメラ移動に併せて移動
	if (pCamera->GetMovable()) {
		XMVECTOR cameraFront = XMLoadFloat3(pCamera->GetMove());
		cameraFront.m128_f32[1] = 0.0f;
		vPos += cameraFront * pCamera->GetSpeed();
	}
	else
	{
		Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GOT_OBJECT3D);
		if (pPlayer)
		{
			vPos += XMLoadFloat3(&pPlayer->GetMove());
		}
	}
	XMStoreFloat3(&m_Position, vPos);
}

void Sky::Draw()
{
	
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
	XMMATRIX worldX = scaleX* rotX /**mCamera*/ *transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);


	ID3D11RasterizerState* rs;
	D3D11_RASTERIZER_DESC rd;
	rd.FillMode = D3D11_FILL_SOLID;
	rd.CullMode = D3D11_CULL_FRONT;
	rd.FrontCounterClockwise = true;
	rd.MultisampleEnable = true;

	Renderer:: GetpDevice()->CreateRasterizerState(&rd, &rs);
//	Renderer::GetpDeviceContext()->RSSetState(Renderer::GetpRS_FillSolid().Get());



	m_Model->Draw();
}

void Sky::Move()
{
	Camera* pCamera = ManagerT::GetScene()->GetGameObject<Camera>(GOT_CAMERA);
	if (pCamera->GetMovable()) return;
	//XMVECTOR direction = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR vPositon;
	vPositon = XMLoadFloat3(&m_Position);
	XMVECTOR vFront = XMLoadFloat3(&m_Front);
	XMVECTOR direction = vFront;
	if (KeyLogger_Press(KL_UP) || KeyLogger_Press(KL_DOWN) || KeyLogger_Press(KL_RIGHT) || KeyLogger_Press(KL_LEFT)) {
		direction = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		if (KeyLogger_Press(KL_UP)) {
		//	XMFLOAT3 temp = *pCamera->GetFront();
			XMFLOAT3 temp = pCamera->GetDirection()->Forward;
			temp.y = 0.0f;
			direction += XMLoadFloat3(&temp);
			m_Speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_DOWN)) {
		//	XMFLOAT3 temp = *pCamera->GetFront();
			XMFLOAT3 temp = pCamera->GetDirection()->Forward;
			temp.y = 0.0f;
			direction -= XMLoadFloat3(&temp);
			m_Speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_RIGHT)) {
		//	direction += XMLoadFloat3(pCamera->GetRight());
			direction += XMLoadFloat3(&pCamera->GetDirection()->Right);
			m_Speed = MOVE_SPEED;
		}
		if (KeyLogger_Press(KL_LEFT)) {
		//	direction -= XMLoadFloat3(pCamera->GetRight());
			direction -= XMLoadFloat3(&pCamera->GetDirection()->Right);
			m_Speed = MOVE_SPEED;
		}
	}
	else{
		m_Speed = 0.0f;
	}
	direction = XMVector3Normalize(direction);
	XMVECTOR cross = XMVector3Cross(vFront, direction);
	m_Sign = cross.m128_f32[1] < 0.0f ? -1 : 1;

	XMVECTOR dot = XMVector3Dot(vFront, direction);
	float fDot = 0.0f;
	XMStoreFloat(&fDot, dot);
	float dir_difference = acosf(fDot);

	float rot = ROTATION_VALUE * m_Sign;
	if (fabsf(dir_difference) <= NEARLY_ZERO_VALUE) {
		dir_difference = 0.0f;
		rot = 0.0f;
	}
	if (rot > dir_difference) {
		rot = dir_difference;
	}
	if (m_Speed <= 0.0f) {
		rot = 0.0f;
	}
	XMMATRIX mtxRot;
	mtxRot = XMMatrixRotationY(rot);
	vFront = XMVector3TransformNormal(vFront, mtxRot);
	XMStoreFloat3(&m_Front, vFront);

	

	vPositon += direction * m_Speed;
	XMStoreFloat3(&m_MoveVector, (direction * m_Speed));
	XMStoreFloat3(&m_Position, vPositon);
}
