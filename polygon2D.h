#pragma once
#include "gameObject.h"

// 2Dポリゴンクラス
class Polygon2D : public GameObject
{
public:
	/*Polygon2D();
	~Polygon2D();*/

	void Init();
	void Uninit();
	void Update();
	void Draw();
	


private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ
};

