#pragma once
#include "gameObject.h"

// �t�F�[�h�Ǘ��N���X
class Fade : public GameObject
{
public:
	// �t�F�[�h�^�C�v
	enum FadeType
	{
		FADE_NONE = -1,
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	};

	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	// �t�F�[�h��ԃZ�b�g
	static void SetFade(FadeType type);

	// �t�F�[�h�^�C�v�Q�b�^�[
	static FadeType GetFadeType();

private:

	static FadeType m_FadeType;				// �t�F�[�h�^�C�v 
	static float m_FadeAlpha;				// �t�F�[�h���l

	ID3D11Buffer* m_VertexBuffer = nullptr;	// ���_�o�b�t�@
};

