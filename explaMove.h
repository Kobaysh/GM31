#pragma once
#include "gameObject.h"

class ExplaMove :public GameObject
{
private:
	ID3D11ShaderResourceView*	m_texture = nullptr;
	ID3D11Buffer*	m_vertexBuffer = nullptr;

	const float TEXTURE_SIZE_X = 204.0f;
	const float TEXTURE_SIZE_Y = 70.0f;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};