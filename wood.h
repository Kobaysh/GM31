#pragma once
#include "gameObject.h"

class Wood : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;			// ���_�o�b�t�@
	ID3D11ShaderResourceView* m_Texture = nullptr;	// �e�N�X�`��
	XMFLOAT2 m_TextureOffset;						// �e�N�X�`���I�t�Z�b�g
	float m_OffsetY;								// �����I�t�Z�b�g
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

