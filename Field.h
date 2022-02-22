#pragma once
#include "gameObject.h"

class Field : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

