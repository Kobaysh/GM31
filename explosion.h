#pragma once
#include "gameObject.h"

class Explosion : public GameObject
{
private:

	ID3D11Buffer*				m_Vertexbuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

