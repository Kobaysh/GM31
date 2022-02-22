#pragma once
#include "gameObject.h"

class Polygon2D : public GameObject
{
public:
	/*Polygon2D();
	~Polygon2D();*/

	void Init();
	void Uninit();
	void Update();
	void Draw();
	


private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
};

