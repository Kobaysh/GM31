#pragma once
#include "gameObject.h"

class MeshField : public GameObject
{
private:

	ID3D11Buffer*				m_vertexBuffer = nullptr;
	ID3D11Buffer*				m_indexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_texture = nullptr;

	int m_vertexCount;
	int m_indexCount;
	int m_primitiveCount;

public:
	void Init(int horizonCnt, int verticalCnt, float horizonSize, float verticalSize);
	void Uninit();
	void Update();
	void Draw();

};

