#pragma once
#include "gameObject.h"

// 爆発エフェクトクラス
class Explosion : public GameObject
{
private:

	ID3D11Buffer*	m_VertexBuffer = nullptr;	// 頂点バッファ			
	static ID3D11ShaderResourceView* m_Texture;	// テクスチャ


	XMFLOAT2 m_TextureOffset;	// テクスチャオフセット
	int m_Frame;				// 経過フレーム
	static int m_AnimationMag;	// アニメーション倍率
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	// テクスチャ解放
	static void ReleaseTexture();
};

