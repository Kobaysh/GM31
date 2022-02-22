#pragma once
#include "gameObject.h"

class ResultLogo : public GameObject
{
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();
	


private:
	const float TEXTURE_SIZE_X = 320.0f;
	const float TEXTURE_SIZE_Y = 86.0f;

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
};

