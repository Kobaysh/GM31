#pragma once
#include "gameObject.h"

// ���U���g�w�i�N���X
class ResultBG : public GameObject
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

