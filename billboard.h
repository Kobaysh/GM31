#pragma once
#include "gameObject.h"

// �r���{�[�h�N���X
class Billboard : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

