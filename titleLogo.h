#pragma once
#include "gameObject.h"

class TitleLogo : public GameObject
{
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();
	


private:


	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
};

