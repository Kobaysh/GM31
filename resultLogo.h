#pragma once
#include "gameObject.h"

// リザルトロゴクラス
class ResultLogo : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:
	const float TEXTURE_SIZE_X = 320.0f;					// テクスチャサイズ幅
	const float TEXTURE_SIZE_Y = 86.0f;						// テクスチャサイズ高さ

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ
};

