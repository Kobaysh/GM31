#pragma once
#include "gameObject.h"

class PressSpaceKey : public GameObject
{
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ

	float m_FadeAlpha;	// フェードα値
};

