#pragma once
#include "gameObject.h"

class MeshField : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11Buffer*				m_IndexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;
	ID3D11RasterizerState* m_RasterrizerState = nullptr;

	VERTEX_3DX* m_PVertex;
//	VERTEX_3DX** m_ppVertex;

	int m_VertexCount;
	int m_IndexCount;
	int m_PrimitiveCount;
	bool m_IsWireFrame;

	int m_HorizonCnt;
	int m_VerticalCnt;
	int m_HorizonSize;
	int m_VerticalSize;

public:
	MeshField():m_PVertex(nullptr){}
	void Init(){}
	void Init(XMFLOAT3 pos, int horizonCnt, int verticalCnt, int horizonSize, int verticalSize);
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(XMFLOAT3 position);

};

