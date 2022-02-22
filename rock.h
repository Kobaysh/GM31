#pragma once
#include "gameObject.h"

// ��I�u�W�F�g�N���X
class Rock : public GameObject
{
private:

//	Model* m_Model;
	int m_ModelId;								// ���f��ID
	class OBB* m_Obb = nullptr;					// �����蔻��

	XMFLOAT3 m_Front;							// �O����

	static ID3D11VertexShader* m_VertexShader;	// ���_�V�F�[�_�[
	static ID3D11PixelShader* m_PixelShader;	// �s�N�Z���V�F�[�_�[
	static ID3D11InputLayout* m_VertexLayout;	// ���_���C�A�E�g


public:
	void Init();
	void Init(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();

	// �O�����Q�b�^�[
	XMFLOAT3* GetFront() { return &m_Front; }

	// �����蔻��Q�b�^�[
	OBB& GetObb() { return *m_Obb; }
};
