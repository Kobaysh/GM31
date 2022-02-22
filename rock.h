#pragma once
#include "gameObject.h"

// 岩オブジェトクラス
class Rock : public GameObject
{
private:

//	Model* m_Model;
	int m_ModelId;								// モデルID
	class OBB* m_Obb = nullptr;					// 当たり判定

	XMFLOAT3 m_Front;							// 前方向

	static ID3D11VertexShader* m_VertexShader;	// 頂点シェーダー
	static ID3D11PixelShader* m_PixelShader;	// ピクセルシェーダー
	static ID3D11InputLayout* m_VertexLayout;	// 頂点レイアウト


public:
	void Init();
	void Init(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();

	// 前方向ゲッター
	XMFLOAT3* GetFront() { return &m_Front; }

	// 当たり判定ゲッター
	OBB& GetObb() { return *m_Obb; }
};
