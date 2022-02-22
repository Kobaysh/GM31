#pragma once
#include "gameObject.h"

// �����G�t�F�N�g�N���X
class Explosion : public GameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = nullptr;	// ���_�o�b�t�@			
	static ID3D11ShaderResourceView* m_Texture;	// �e�N�X�`��


	XMFLOAT2 m_TextureOffset;	// �e�N�X�`���I�t�Z�b�g
	int m_Frame;				// �o�߃t���[��
	static int m_AnimationMag;	// �A�j���[�V�����{��
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	// �e�N�X�`�����
	static void ReleaseTexture();
};

