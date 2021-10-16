#pragma once
#include "gameObject.h"

class PressSpaceKey : public GameObject
{
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_texture = NULL;

	float m_fadeAlpha;
};

