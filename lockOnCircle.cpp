#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "scene.h"
#include "lockOnCircle.h"

const std::string LockOnCircle::TEXTURE_FILE_NAME = "asset\\texture\\circle.png";

void LockOnCircle::Init()
{
	Texture::Load(TEXTURE_FILE_NAME);

	m_Position = m_object->GetPosition();
	m_Scale = XMFLOAT3(1.5f, 1.5f, 1.0f);

	VERTEX_3DX vertex[4];
	vertex[0].Position	= XMFLOAT3(-0.5f, 0.5f, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(+0.5f, 0.5f, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(-0.5f, -0.5f, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(0.5f, -0.5f, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};
	ZeroMemory(&bd, sizeof(bd));
	//	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;	// ���_�o�b�t�@�𓮓I�ύX�\��
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4; // �o�C�g��
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
											//	bd.CPUAccessFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	D3D11_SUBRESOURCE_DATA sd{};
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/unlitTexturePS.cso");

}

void LockOnCircle::Uninit()
{
	m_VertexBuffer->Release();
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void LockOnCircle::Update()
{
	m_Position = m_object->GetPosition();
}

void LockOnCircle::Draw()
{
	// ���_�f�[�^����������
	//D3D11_MAPPED_SUBRESOURCE msr;
	//Renderer::GetpDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	//{
	//	VERTEX_3DX* vertex = (VERTEX_3DX*)msr.pData;
	//	float offsetY = m_Scale.y;
	//	float posX = SCREEN_WIDTH * 0.5f;
	//	float posY = SCREEN_HEIGHT * 0.5f;

	//	//vertex[0].Position	= XMFLOAT3(m_Position.x -0.5f * m_Scale.x,m_Position.y + 0.5f* m_Scale.y - offsetY, 0.0f);
	//	//vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//	//vertex[1].Position = XMFLOAT3(m_Position.x +0.5f* m_Scale.x,m_Position.y  + 0.5f* m_Scale.y- offsetY, 0.0f);
	//	//vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//	//vertex[2].Position = XMFLOAT3(m_Position.x -0.5f* m_Scale.x,m_Position.y  -0.5f* m_Scale.y- offsetY, 0.0f);
	//	//vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//	//vertex[3].Position = XMFLOAT3(m_Position.x + 0.5f* m_Scale.x,m_Position.y  -0.5f* m_Scale.y- offsetY, 0.0f);
	//	//vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	//vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	//vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);

	//	vertex[0].Position	= XMFLOAT3(posX -0.5f * m_Scale.x,posY + 0.5f* m_Scale.y - offsetY, 0.0f);
	//	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	//	vertex[1].Position = XMFLOAT3(posX +0.5f* m_Scale.x,posY  + 0.5f* m_Scale.y- offsetY, 0.0f);
	//	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	//	vertex[2].Position = XMFLOAT3(posX -0.5f* m_Scale.x,posY  -0.5f* m_Scale.y- offsetY, 0.0f);
	//	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	//	vertex[3].Position = XMFLOAT3(posX + 0.5f* m_Scale.x,posY  -0.5f* m_Scale.y- offsetY, 0.0f);
	//	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	//	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);
	//}
	//Renderer::GetpDeviceContext()->Unmap(m_VertexBuffer, 0);
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
//	Renderer::SetWorldMatrixX(&world4x4);

	Renderer::SetWorldViewProjection2D(&world4x4);



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �e�N�X�`���ݒ�
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, Texture::GetTexture(TEXTURE_FILE_NAME));

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
