#pragma once
#include "gameObject.h"

// �ǃI�u�W�F�N�g�N���X
class Wall : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��
	class OBB* m_Obb = nullptr;								// �����蔻��
	int m_ModelId;											// ���f��ID
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

