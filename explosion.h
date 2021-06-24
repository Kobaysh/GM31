#pragma once
#include "gameObject.h"

class Explosion : public GameObject
{
private:

	ID3D11Buffer*				m_Vertexbuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;


	XMFLOAT2 m_textureOffset;	
	int m_frame;
	static int m_animationMag;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

