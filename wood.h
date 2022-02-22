#pragma once
#include "gameObject.h"

class Wood : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;


	XMFLOAT2 m_TextureOffset;	
	float m_OffsetY;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

