#pragma once
#include "gameObject.h"

class ExplaChange :public GameObject
{
private:
	ID3D11ShaderResourceView* m_Texture;		// �e�N�X�`��
	ID3D11Buffer*	m_VertexBuffer = nullptr;	// ���_�o�b�t�@

	const float TEXTURE_SIZE_X = 144.0f;		// �e�N�X�`���T�C�Y��
	const float TEXTURE_SIZE_Y = 52.0f;			// �e�N�X�`���T�C�Y����
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};