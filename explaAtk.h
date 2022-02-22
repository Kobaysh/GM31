#pragma once
#include "gameObject.h"

// 攻撃説明クラス
class ExplaAtk :public GameObject
{
private:
	ID3D11ShaderResourceView* m_TextureKey;		// キーボード用テクスチャ
	ID3D11ShaderResourceView* m_TextureMouse;	// マウス用テクスチャ
	ID3D11Buffer*	m_VertexBuffer = nullptr;	// 頂点バッファ

	const float TEXTURE_SIZE_X = 144.0f;		// テクスチャサイズ幅
	const float TEXTURE_SIZE_Y = 52.0f;			// テクスチャサイズ高さ
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
};