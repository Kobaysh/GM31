#pragma once
#include "gameObject.h"

// �Ԗڏ�n�`�N���X
class MeshField : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11Buffer*				m_IndexBuffer = nullptr;	// �C���f�b�N�X�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��
	ID3D11RasterizerState* m_RasterrizerState = nullptr;	// ���X�^���C�U�X�e�[�g

	VERTEX_3DX* m_Vertex;									// ���_���
//	VERTEX_3DX** m_ppVertex;

	int m_VertexCount;										// ���_��
	int m_IndexCount;										// �C���f�b�N�X��
	int m_PrimitiveCount;									// �v���~�e�B�u��
	bool m_IsWireFrame;										// ���C���t���[����
															
	int m_HorizonCnt;										// ����������
	int m_VerticalCnt;										// ����������
	int m_HorizonSize;										// ���������T�C�Y
	int m_VerticalSize;										// ���������T�C�Y

public:
	MeshField():m_Vertex(nullptr){}
	void Init(){}
	void Init(XMFLOAT3 pos, int horizonCnt, int verticalCnt, int horizonSize, int verticalSize);
	void Uninit();
	void Update();
	void Draw();

	// �w����W�̒n�`�̍������擾
	float GetHeight(XMFLOAT3 position);

};

