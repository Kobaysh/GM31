#pragma once
#include "gameObject.h"

class ExplaAtk :public GameObject
{
private:
	ID3D11ShaderResourceView* m_textureKey;
	ID3D11ShaderResourceView* m_textureMouse;
	ID3D11Buffer*	m_vertexBuffer = nullptr;

	const float TEXTURE_SIZE_X = 144.0f;
	const float TEXTURE_SIZE_Y = 52.0f;
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};