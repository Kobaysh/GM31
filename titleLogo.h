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


	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;


	ID3D11Buffer*				m_VertexBuffer2 = nullptr;
	ID3D11ShaderResourceView*	m_texture2 = nullptr;
};

