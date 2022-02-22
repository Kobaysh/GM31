#pragma once
#include "gameObject.h"

// �^�C�g�����S�N���X
class TitleLogo : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// ���_�o�b�t�@
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// �e�N�X�`��


	ID3D11Buffer*				m_VertexBuffer2 = nullptr;	// ���_�o�b�t�@2
	ID3D11ShaderResourceView*	m_Texture2 = nullptr;		// �e�N�X�`��2
};

