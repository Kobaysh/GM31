#pragma once
#include "gameObject.h"

class Explosion : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	static ID3D11ShaderResourceView*	m_Texture;


	XMFLOAT2 m_textureOffset;	
	int m_Frame;
	static int m_animationMag;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	static void ReleaseTexture();
};

