#include "main.h"
#include "renderer.h"
#include "explaDef.h"
#include "texture.h"
#include "input.h"

void ExplaDef::Init()
{
	VERTEX_3DX vertex[4];
	float x, y, sx, sy;
	x = SCREEN_WIDTH / 20;
	y = SCREEN_HEIGHT / 4 + 70.0f + TEXTURE_SIZE_Y + TEXTURE_SIZE_Y;
	sx = TEXTURE_SIZE_X;
	sy = TEXTURE_SIZE_Y;
//	x -= sx / 2;
	vertex[0].Position	= XMFLOAT3(x, y, 0.0f);
	vertex[0].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position = XMFLOAT3(x + sx, y, 0.0f);
	vertex[1].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position = XMFLOAT3(x, y + sy, 0.0f);
	vertex[2].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position = XMFLOAT3(x + sx, y + sy, 0.0f);
	vertex[3].Normal	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse	= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = XMFLOAT2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = vertex;

	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset\\texture\\o_def.png",
		NULL,
		NULL,
		&m_textureKey,
		NULL
	);
	assert(m_textureKey);

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset\\texture\\mouse_def.png",
		NULL,
		NULL,
		&m_textureMouse,
		NULL
	);
	assert(m_textureMouse);


	Renderer::CreateVertexShader(&m_vertexShader, &m_vertexLayout, "asset/shader/unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_pixelShader, "asset/shader/unlitTexturePS.cso");
}

void ExplaDef::Uninit()
{
	m_textureKey->Release();
	m_textureMouse->Release();
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_vertexLayout->Release();
}

void ExplaDef::Update()
{
}

void ExplaDef::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetpDeviceContext()->IASetInputLayout(m_vertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_vertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_pixelShader, NULL, 0);

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// �e�N�X�`���ݒ�
	if (Input::GetMouseActive())
	{
		Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_textureMouse);
	}
	else
	{
		Renderer::GetpDeviceContext()->PSSetShaderResources(0, 1, &m_textureKey);

	}
	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetpDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetpDeviceContext()->Draw(4, 0);

}