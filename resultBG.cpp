#include "main.h"
#include "renderer.h"
#include "resultBG.h"


#define FILENAME ("asset/texture/result.jpg")

void ResultBG::Init()
{
	VERTEX_3DX vertexx[4];
	vertexx[0].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[0].TexCoord = XMFLOAT2(0.0f, 0.0f);
		  
	vertexx[1].Position = XMFLOAT3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertexx[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[1].TexCoord = XMFLOAT2(1.0f, 0.0f);
		  
	vertexx[2].Position = XMFLOAT3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertexx[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[2].TexCoord = XMFLOAT2(0.0f, 1.0f);
		  
	vertexx[3].Position = XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertexx[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertexx[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertexx[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertexx;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
	//	Renderer::GetDevice(),
		Renderer::GetpDevice().Get(),
		FILENAME,
		NULL,
		NULL,
		&m_texture,
		NULL
		);
	assert(m_texture);

	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_pixelShader, "asset/shader/unlitTexturePS.cso");


}

void ResultBG::Uninit()
{
	m_VertexBuffer->Release();
	m_texture->Release();

	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
}

void ResultBG::Update()
{
}

void ResultBG::Draw()
{

	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;

	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �e�N�X�`���ݒ�
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetpDeviceContext()->Draw(4, 0);
	

}