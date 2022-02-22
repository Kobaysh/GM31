#pragma once
#include "gameObject.h"

// �n�`�N���X
class Field : public GameObject
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

