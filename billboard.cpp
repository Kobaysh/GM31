#include "billboard.h"
#include "camera.h"
#include "manager.h"
#include "scene.h"

void Billboard::Init()
{
}

void Billboard::Uninit()
{
}

void Billboard::Update()
{
}

void Billboard::Draw()
{
	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);
	
	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	Scene* scene = ManagerT::GetScene();
	XMMATRIX view = XMLoadFloat4x4(scene->GetGameObject<Camera>(GOT_CAMERA)->GetView());
	
	XMFLOAT4X4 temp;
	XMStoreFloat4x4(&temp, view);
	temp._41 = 0.0f;
	temp._42 = 0.0f;
	temp._43 = 0.0f;
	view = XMLoadFloat4x4(&temp);

	XMMATRIX invView = XMMatrixTranspose(view);


	XMMATRIX scaleX = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_rotation.x, m_rotation.y, m_rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_position.x, m_position.y, m_position.z);
	XMMATRIX worldX = scaleX * rotX * invView * transX;
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);


	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Emission = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	Renderer::SetMaterial(material);


	// �e�N�X�`���ݒ�
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetpDeviceContext()->Draw(4, 0);
}
