#pragma once
#include "singleton.h"
class Title:SingletonT<Title>
{
private:
	ID3D11Buffer*				m_Vertexbuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	ID3D11VertexShader*		m_VertexShader = NULL;
	ID3D11PixelShader*		m_PixelShader = NULL;
	ID3D11InputLayout*		m_VertexLayout = NULL;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

