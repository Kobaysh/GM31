#include "main.h"
#include "renderer.h"
#include "meshField.h"

void MeshField::Init(int horizonCnt, int verticalCnt, float horizonSize, float verticalSize)
{

	int  HLength = horizonCnt * horizonSize;
	int  VLength = verticalCnt * verticalSize;
	// �c���̔䗦�ŕ��ו���ς���ꍇ
	int high, low;
	if (horizonCnt > verticalCnt) {
		// ���������ꍇ
		high = horizonCnt;
		low = verticalCnt;
	}
	else {
		// �c�������A�����̏ꍇ
		high = verticalCnt;
		low = horizonCnt;
	}
	// ���_���̌v�Z
	int rowVertex = verticalCnt + 1;		// �s�̒��_��
	int colVertex = horizonCnt + 1;			// ��̒��_��
	m_vertexCount = rowVertex * colVertex;	// �S�̂̒��_��
	// �C���f�b�N�X���ƃv���~�e�B�u���̌v�Z
	m_indexCount = (high + 1) * 2 * low + (low - 1) * 2;
	m_primitiveCount = high * low * 2 + (low - 1) * 4;

	// �J�n���W
	float startX = -horizonCnt * horizonSize * 0.5f;
	float startZ = verticalCnt * verticalSize * 0.5f;

	VERTEX_3DX* pVertex = new VERTEX_3DX[m_vertexCount];
	for (int z = 0, i = 0; z < rowVertex; z++) {
		for (int x = 0; x < colVertex; x++, i++) {
			pVertex[i].Position = XMFLOAT3(startX + x * horizonSize, 0.0f, startZ - z * verticalCnt);
			pVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			pVertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			pVertex[i].TexCoord = XMFLOAT2((float)x, (float)z);
		}
	}

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd{};

	bd.Usage = D3D11_USAGE_DEFAULT;	bd.ByteWidth = sizeof(VERTEX_3DX) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd{};
	sd.pSysMem = pVertex;
	Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_vertexBuffer);

	delete[] pVertex;

	// �C���f�b�N�X�o�b�t�@����
	WORD* pI = new WORD[m_indexCount];
	if (high == horizonCnt) {	// ���ɕ��ׂ�ꍇ
		for (int ZCnt = 0, loopCnt = 0, HVCnt = 0; ZCnt < verticalCnt; ZCnt++) {
			for (int XCnt = 0; XCnt < (horizonCnt + 1) * 2; XCnt++) {

				if (loopCnt % 2 == 0) {
					// �����̏ꍇ
					pI[loopCnt] = (WORD)(horizonCnt + 1 + HVCnt);
				}
				else {
					// ��̏ꍇ
					pI[loopCnt] = (WORD)HVCnt;
					HVCnt++;
				}

				loopCnt++;
			}

			//���s���ɏk�ރ|���S���p�̃C���f�b�N�X��ǉ�����
			if (loopCnt < m_indexCount) {
				//�n�_
				pI[loopCnt] = pI[loopCnt - 1];
				loopCnt++;
				//�I�_
				pI[loopCnt] = (WORD)(horizonCnt + 1 + HVCnt);
				loopCnt++;
			}
		}
	}
	else if (high == verticalCnt) {	// �c�ɕ��ׂ�ꍇ
		for (int XCnt = 0, loopCnt = 0, VVCnt = 0; XCnt < horizonCnt; XCnt++, VVCnt = 0) {
			for (int ZCnt = 0; ZCnt < (verticalCnt + 1) * 2; ZCnt++) {

				if (loopCnt % 2 == 0) {
					// �����̏ꍇ
					pI[loopCnt] = (WORD)(colVertex * VVCnt + XCnt);
				}
				else {
					// ��̏ꍇ
					pI[loopCnt] = pI[loopCnt - 1] + 1;
					VVCnt++;
				}

				loopCnt++;
			}

			//���s���ɏk�ރ|���S���p�̃C���f�b�N�X��ǉ�����
			if (loopCnt < m_indexCount) {
				//�n�_
				pI[loopCnt] = pI[loopCnt - 1];
				loopCnt++;

				//�I�_
				pI[loopCnt] = (WORD)(XCnt + 1);
				loopCnt++;
			}
		}
	}




	delete[] pI;

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset/texture/grass02.jpg",
		NULL,
		NULL,
		&m_texture,
		NULL
	);
	assert(m_texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
}

void MeshField::Uninit()
{
	m_vertexBuffer->Release();
	m_texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void MeshField::Update()
{

}

void MeshField::Draw()
{
	// ���̓��C�A�E�g
	Renderer::GetpDeviceContext()->IASetInputLayout(m_VertexLayout);

	// �V�F�[�_�[�ݒ�
	Renderer::GetpDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetpDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	// �}�g���N�X

	XMMATRIX scaleX = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	XMMATRIX rotX = XMMatrixRotationRollPitchYaw(m_Rotation.x,m_Rotation.y,m_Rotation.z);
	XMMATRIX transX = XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	XMMATRIX worldX = scaleX * rotX * transX;
	Renderer::SetWorldMatrixX(&worldX);



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
