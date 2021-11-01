#pragma once
#include "gameObject.h"

class MeshField : public GameObject
{
private:

	ID3D11Buffer*				m_vertexBuffer = nullptr;
	ID3D11Buffer*				m_indexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_texture = nullptr;
	ID3D11RasterizerState* m_pRasterrizerState = nullptr;

	VERTEX_3DX* m_pVertex;
//	VERTEX_3DX** m_ppVertex;

	int m_vertexCount;
	int m_indexCount;
	int m_primitiveCount;
	bool m_isWireFrame;

	int m_horizonCnt;
	int m_verticalCnt;
	int m_horizonSize;
	int m_verticalSize;

public:
	MeshField():m_pVertex(nullptr){}
	void Init(){}
	void Init(XMFLOAT3 pos, int horizonCnt, int verticalCnt, float horizonSize, float verticalSize);
	void Uninit();
	void Update();
	void Draw();

	float GetHeight(XMFLOAT3 position);

};

