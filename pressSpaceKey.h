#pragma once
#include "gameObject.h"

// �X�y�[�X�L�[�ҋ@�N���X
class PressSpaceKey : public GameObject
{
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��

	float m_FadeAlpha;	// �t�F�[�h���l
};

