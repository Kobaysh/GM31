#include "main.h"
#include "renderer.h"
#include "meshField.h"
#include "keylogger.h"

const static float testField[21][21] = {
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.5f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+0.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+2.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+2.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.5f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,+0.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+2.0f,+1.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+3.0f,+1.0f,+0.0f,-1.0f,-2.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+1.0f,+2.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.5f,+1.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
};
//const static float testField[21][21] = {
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,-0.0f,-0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,-0.0f,-0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,-0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,-0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,-0.0f,-0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,-0.0f,-0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//	+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,+0.0f,
//};



void MeshField::Init(XMFLOAT3 pos, int horizonCnt, int verticalCnt, int horizonSize, int verticalSize)
{
	m_HorizonCnt = horizonCnt;
	m_VerticalCnt = verticalCnt;
	m_HorizonSize = horizonSize;
	m_VerticalSize = verticalSize;
	m_Position = pos;
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	m_IsWireFrame = false;

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
	m_VertexCount = rowVertex * colVertex;	// �S�̂̒��_��
	// �C���f�b�N�X���ƃv���~�e�B�u���̌v�Z
	m_IndexCount = (high + 1) * 2 * low + (low - 1) * 2;
	m_PrimitiveCount = high * low * 2 + (low - 1) * 4;

	// �J�n���W
	float startX = m_Position.x - horizonCnt * horizonSize * 0.5f;
	float startZ = m_Position.z + verticalCnt * verticalSize * 0.5f;

	m_PVertex = new VERTEX_3DX[m_VertexCount];

	//VERTEX_3DX** m_ppVertex = new VERTEX_3DX*[colVertex];
	//for (int i = 0; i < colVertex; i++) {
	//	m_ppVertex[i] = new VERTEX_3DX[rowVertex];
	//}
	//for (int z = 0; z < rowVertex; z++) {
	//	for (int x = 0; x < colVertex; x++) {
	//		m_ppVertex[x][z].Position = XMFLOAT3(startX + x * horizonSize, sinf(x) * cosf(z), startZ - z * verticalSize);
	//		m_ppVertex[x][z].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//		m_ppVertex[x][z].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	//		m_ppVertex[x][z].TexCoord = XMFLOAT2((float)x, (float)z);
	//	}
	//}
	for (int z = 0, i = 0; z < rowVertex; z++) {
		for (int x = 0; x < colVertex; x++, i++) {
		//	m_PVertex[i].Position = XMFLOAT3(startX + x * horizonSize,x * 0.05f + z * 0.05f, startZ - z * verticalSize);
		//	m_PVertex[i].Position = XMFLOAT3(startX + x * horizonSize, cosf(x) * sinf(z) * 2.0f, startZ - z * verticalSize);
			m_PVertex[i].Position = XMFLOAT3(startX + x * horizonSize, testField[z][x] * 2.0f, startZ - z * verticalSize);
			m_PVertex[i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);
			m_PVertex[i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			m_PVertex[i].TexCoord = XMFLOAT2((float)x, (float)z);
		}
	}

	// �@���x�N�g���Z�o
	for (int x = 1; x < horizonCnt; x++) {
		for (int z = 1; z < verticalCnt; z++) {
			XMVECTOR vx, vz, vn;
			vx = XMLoadFloat3(&m_PVertex[(x + 1) + z * (horizonCnt + 1)].Position) - XMLoadFloat3(&m_PVertex[(x - 1) + z * (horizonCnt + 1)].Position);
			vz = XMLoadFloat3(&m_PVertex[x + (z - 1) *(horizonCnt + 1)].Position) - XMLoadFloat3(&m_PVertex[x + (z+ 1) * (horizonCnt + 1)].Position);
			vn = XMVector3Cross(vz, vx);
		 	vn = XMVector3Normalize(vn);
			XMStoreFloat3(&m_PVertex[x + z * (horizonCnt + 1)].Normal, vn);
		}
	}
	//for (int x = 1; x <= horizonCnt - 1; x++) {
	//	for (int z = 1; z <= verticalCnt - 1; z++) {
	//		XMVECTOR vx, vz, vn;
	//		vx = DirectX::XMLoadFloat3(&m_ppVertex[x+1][z].Position) - DirectX::XMLoadFloat3(&m_ppVertex[x - 1][z].Position);
	//		vz = DirectX::XMLoadFloat3(&m_ppVertex[x][z-1].Position) - DirectX::XMLoadFloat3(&m_ppVertex[x][z + 1].Position);
	//		vn = XMVector3Cross(vz, vx);
	//		vn = XMVector3Normalize(vn);
	//		DirectX::XMStoreFloat3(&m_ppVertex[x][z].Normal, vn);
	//	}
	//}

	{
		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd{};
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;	
		bd.ByteWidth = sizeof(VERTEX_3DX) * m_VertexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;// �o�b�t�@�̎��
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd{};
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_PVertex;
//		sd.pSysMem = m_ppVertex;
		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	{
		// �C���f�b�N�X�o�b�t�@����
		unsigned int* pI = new unsigned int[m_IndexCount];
	/*	int i = 0;
		for (int x = 0; x < colVertex; x++) {
			for (int z = 0; z < rowVertex; z++, i++) {
				pI[i] = x * colVertex + z;
				i++;

				pI[i] = (x + 1) * colVertex + z;
				i++;
			}
			if (x == colVertex - 1) break;

			pI[i] = (x + 1) * rowVertex + colVertex;

			i++;

			pI[i] = (x + 1)*rowVertex;
			i++;
		}*/
		
		if (high == horizonCnt) {	// ���ɕ��ׂ�ꍇ
			for (int ZCnt = 0, i = 0, HVCnt = 0; ZCnt < verticalCnt; ZCnt++) {
				for (int XCnt = 0; XCnt < colVertex * 2; XCnt++) {

					if (i % 2 == 0) {
						// �����̏ꍇ
						pI[i] = (unsigned int)(colVertex + HVCnt);
					}
					else {
						// ��̏ꍇ
						pI[i] = (unsigned int)HVCnt;
						HVCnt++;
					}

					i++;
				}

				//���s���ɏk�ރ|���S���p�̃C���f�b�N�X��ǉ�����
				if (i < m_IndexCount) {
					//�n�_
					pI[i] = pI[i - 1];
					i++;
					//�I�_
					pI[i] = (unsigned int)(colVertex + HVCnt);
					i++;
				}
			}
		}
		else if (high == verticalCnt) {	// �c�ɕ��ׂ�ꍇ
			for (int XCnt = 0, i = 0, VVCnt = 0; XCnt < horizonCnt; XCnt++, VVCnt = 0) {
				for (int ZCnt = 0; ZCnt < rowVertex * 2; ZCnt++) {

					if (i % 2 == 0) {
						// �����̏ꍇ
						pI[i] = (unsigned int)(colVertex * VVCnt + XCnt);
					}
					else {
						// ��̏ꍇ
						pI[i] = pI[i - 1] + 1;
						VVCnt++;
					}

					i++;
				}

				//���s���ɏk�ރ|���S���p�̃C���f�b�N�X��ǉ�����
				if (i < m_IndexCount) {
					//�n�_
					pI[i] = pI[i - 1];
					i++;

					//�I�_
					pI[i] = (unsigned int)(XCnt + 1);
					i++;
				}
			}
		}
		
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned int)* m_IndexCount;
		bd.BindFlags = D3D10_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = pI;

		Renderer::GetpDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);

		delete[] pI;
	}


	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(
		Renderer::GetpDevice().Get(),
		"asset/texture/grass02.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL
	);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "asset/shader/vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "asset/shader/vertexLightingPS.cso");

}

void MeshField::Uninit()
{
	if (m_PVertex) {
		delete[] m_PVertex;
	}
//	delete[] m_ppVertex;

	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void MeshField::Update()
{
#if defined(DEBUG) || defined (_DEBUG)
	if (KeyLogger_Trigger(KL_WIRE)) {
		m_IsWireFrame = m_IsWireFrame == true ? false : true;
	}
#endif
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
	XMFLOAT4X4 world4x4;
	XMStoreFloat4x4(&world4x4, worldX);
	Renderer::SetWorldMatrixX(&world4x4);



	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3DX);
	UINT offset = 0;
	Renderer::GetpDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�ݒ�
	Renderer::GetpDeviceContext()->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	
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

	if (m_IsWireFrame) {
		D3D11_RASTERIZER_DESC rdc{};
		rdc.FillMode = D3D11_FILL_WIREFRAME;
		rdc.CullMode = D3D11_CULL_NONE;
		rdc.FrontCounterClockwise = true;
		Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_RasterrizerState);
		Renderer::GetpDeviceContext()->RSSetState(m_RasterrizerState);
		//Renderer::GetpDeviceContext()->RSSetState(Renderer::GetpRS_FillWireFrame().Get());
	}

	// �|���S���`��
	Renderer::GetpDeviceContext()->DrawIndexed(m_IndexCount, 0, 0);
	if (m_IsWireFrame) {
		D3D11_RASTERIZER_DESC rdc{};
		rdc.FillMode = D3D11_FILL_SOLID;
		rdc.CullMode = D3D11_CULL_FRONT;
		rdc.FrontCounterClockwise = true;
		Renderer::GetpDevice()->CreateRasterizerState(&rdc, &m_RasterrizerState);
		Renderer::GetpDeviceContext()->RSSetState(m_RasterrizerState);
		//Renderer::GetpDeviceContext()->RSSetState(Renderer::GetpRS_FillSolid().Get());
	}
}

float MeshField::GetHeight(XMFLOAT3 position)
{
	int x, z;
	x = (int)(position.x / (float)m_HorizonSize * 1.0f + m_HorizonCnt* 0.5f);
	z = m_VerticalCnt - (int)(position.z / (float)m_VerticalSize * 1.0f + m_VerticalCnt * 0.5f);

	if (x > m_HorizonCnt + 1 || z > m_VerticalCnt + 1) {
		return position.y - 0.5f;
	}

	XMFLOAT3 pos0, pos1, pos2, pos3,vecc;
	pos0 = m_PVertex[(x + 0) + (z + 0) * (m_HorizonCnt + 1)].Position;
	pos1 = m_PVertex[(x + 1) + (z + 0) * (m_HorizonCnt + 1)].Position;
	pos2 = m_PVertex[(x + 0) + (z + 1) * (m_HorizonCnt + 1)].Position;
	pos3 = m_PVertex[(x + 1) + (z + 1) * (m_HorizonCnt + 1)].Position;
	//pos0 = m_vertex[x + 0][z + 0].Position;
	//pos1 = m_vertex[x + 1][z + 0].Position;
	//pos2 = m_vertex[x + 0][z + 1].Position;
	//pos3 = m_vertex[x + 1][z + 1].Position;

	XMVECTOR v12, v1p, c;
	v12 = XMLoadFloat3(&pos2) - XMLoadFloat3(&pos1);
	v1p = XMLoadFloat3(&position) - XMLoadFloat3(&pos1);

	c = XMVector3Cross(v12, v1p);

	XMStoreFloat3(&vecc, c);

	float py;
	XMVECTOR n;

	if (vecc.y > 0.0f) {
		XMVECTOR v10;
		v10 = XMLoadFloat3(&pos0) - XMLoadFloat3(&pos1);
		n = XMVector3Cross(v10, v12);
	}
	else
	{
		XMVECTOR v13;
		v13 = XMLoadFloat3(&pos3) - XMLoadFloat3(&pos1);
		n = XMVector3Cross(v12, v13);
	}

	XMFLOAT3 nn;
	XMStoreFloat3(&nn, n);

	py = -((position.x - pos1.x) * nn.x + (position.z - pos1.z) * nn.z) / nn.y + pos1.y;


	return py;
}
