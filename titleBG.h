#pragma once
#include "gameObject.h"

// �^�C�g���w�i�N���X
class TitleBG : public GameObject
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��
};