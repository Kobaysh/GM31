#pragma once
#include "gameObject.h"

// ���U���g���S�N���X
class ResultLogo : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	const float TEXTURE_SIZE_X = 320.0f;					// �e�N�X�`���T�C�Y��
	const float TEXTURE_SIZE_Y = 86.0f;						// �e�N�X�`���T�C�Y����

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��
};

