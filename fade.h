#pragma once
#include "gameObject.h"

class Fade : public GameObject
{
public:

	enum FadeType
	{
		FADE_NONE = -1,
		FADE_IN,
		FADE_OUT,
		FADE_MAX
	};

	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	static void SetFade(FadeType type);
	static FadeType GetFadeType();

private:

	static FadeType m_FadeType;
	static float m_FadeAlpha;

	ID3D11Buffer*				m_VertexBuffer = NULL;
//	ID3D11ShaderResourceView*	m_Texture = NULL;
};

