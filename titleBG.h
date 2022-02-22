#pragma once
#include "gameObject.h"

// タイトル背景クラス
class TitleBG : public GameObject
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ
};