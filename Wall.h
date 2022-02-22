#pragma once
#include "gameObject.h"

// 壁オブジェクトクラス
class Wall : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ
	class OBB* m_Obb = nullptr;								// 当たり判定
	int m_ModelId;											// モデルID
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

