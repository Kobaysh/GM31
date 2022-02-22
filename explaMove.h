#pragma once
#include "gameObject.h"

class ExplaMove :public GameObject
{
private:
	ID3D11ShaderResourceView*	m_Texture = nullptr;	// テクスチャ
	ID3D11Buffer*	m_VertexBuffer = nullptr;			// 頂点バッファ

	const float TEXTURE_SIZE_X = 204.0f;				// テクスチャサイズ幅
	const float TEXTURE_SIZE_Y = 70.0f;					// テクスチャサイズ高さ
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};