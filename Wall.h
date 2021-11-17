#pragma once
#include "gameObject.h"
class Wall : public GameObject
{
private:
	ID3D11Buffer*				m_vertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_texture = NULL;
	class Model*  m_model;
	int m_modelId;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

