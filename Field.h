#pragma once
#include "gameObject.h"

// 地形クラス
class Field : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

