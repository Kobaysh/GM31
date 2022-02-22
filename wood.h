#pragma once
#include "gameObject.h"

class Wood : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_texture = NULL;


	XMFLOAT2 m_textureOffset;	
	float m_offsetY;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

