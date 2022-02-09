#include "main.h"
#include "renderer.h"
#include "resultLogo.h"


#define FILENAME ("asset/texture/kusodekaresult.png")

void ResultLogo::Init()
{
	/*VERTEX_3D vertex[4];
	vertex[0].Position	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= D3DXVECTOR2(0.0f, 0.0f);
	
	vertex[1].Position	= D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position	= D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position	= D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= D3DXVECTOR2(1.0f, 1.0f);*/

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
//	bd.ByteWidth = sizeof(VERTEX_3D) * 4;	// �o�C�g��
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	//sd.pSysMem = vertex;
	sd.pSysMem = vertexx;

	//Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
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

void ResultLogo::Uninit()
{
	m_VertexBuffer->Release();
	m_texture->Release();

	m_vertexLayout->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
}

void ResultLogo::Update()
{
}

void ResultLogo::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	//Renderer::GetDeviceContext()->IASetInputLayout(m_pVertexLayout);

	//// �V�F�[�_�[�ݒ�
	//Renderer::GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	//Renderer::GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);

	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	//Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	//// �e�N�X�`���ݒ�
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	//// �v���~�e�B�u�g�|���W�ݒ�
	//Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//// �|���S���`��
	//Renderer::GetDeviceContext()->Draw(4, 0);
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �e�N�X�`���ݒ�
	Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetpDeviceContext()->Draw(4, 0);
	

}
