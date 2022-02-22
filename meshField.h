#pragma once
#include "gameObject.h"

// 網目状地形クラス
class MeshField : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11Buffer*				m_IndexBuffer = nullptr;	// インデックスバッファ
	ID3D11ShaderResourceView*	m_Texture = nullptr;		// テクスチャ
	ID3D11RasterizerState* m_RasterrizerState = nullptr;	// ラスタライザステート

	VERTEX_3DX* m_Vertex;									// 頂点情報
//	VERTEX_3DX** m_ppVertex;

	int m_VertexCount;										// 頂点数
	int m_IndexCount;										// インデックス数
	int m_PrimitiveCount;									// プリミティブ数
	bool m_IsWireFrame;										// ワイヤフレームか
															
	int m_HorizonCnt;										// 水平方向個数
	int m_VerticalCnt;										// 垂直方向個数
	int m_HorizonSize;										// 水平方向サイズ
	int m_VerticalSize;										// 垂直方向サイズ

public:
	MeshField():m_Vertex(nullptr){}
	void Init(){}
	void Init(XMFLOAT3 pos, int horizonCnt, int verticalCnt, int horizonSize, int verticalSize);
	void Uninit();
	void Update();
	void Draw();

	// 指定座標の地形の高さを取得
	float GetHeight(XMFLOAT3 position);

};

