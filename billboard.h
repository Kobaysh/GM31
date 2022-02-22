#pragma once
#include "gameObject.h"

class Billboard : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_texture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

