#include "main.h"
#include "renderer.h"
#include "explosion.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"

#define FILENAME ("asset/texture/explosion.png")

void Explosion::Init()
{
	VERTEX_3DX vertexx[4];
	vertexx[0].Position = XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertexx[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexx[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertexx[1].Position = XMFLOAT3(0.5f, 0.5f, 0.0f);
	vertexx[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexx[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertexx[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertexx[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexx[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertexx[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertexx[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
	vertexx[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4; // �o�C�g��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;
	sd.pSysMem = vertexx;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_Vertexbuffer);

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		//Renderer::GetDevice(),
		Renderer::GetpDevice().Get(),
		FILENAME,
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Position = XMFLOAT3(0.0f, 3.0f, 10.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void Explosion::Uninit()
{
	m_Vertexbuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Explosion::Update()
{
}

void Explosion::Draw()
{
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�

	Scene* scene = ManagerT::GetScene();
	XMMATRIX mtxInvView;
	XMMATRIX view =XMLoadFloat4x4(&scene->GetGameObject<Camera>()->GetView());
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, view);
	temp._41 = 0.0f;
	temp._42 = 0.0f;
	temp._43 = 0.0f;
    view =	XMLoadFloat4x4(&temp);

	mtxInvView = XMMatrixTranspose(view);
//	mtxInvView = XMMatrixInverse(nullptr, mtxInvView);
	
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = mtxInvView * transX;
	Renderer::SetWorldMatrixX(&worldX);



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_Vertexbuffer, &stride, &offset);


	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	Renderer::SetMaterial(material);


	// �e�N�X�`���ݒ�
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
