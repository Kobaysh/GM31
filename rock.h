#pragma once
#include "gameObject.h"

class Rock : public GameObject
{
private:

//	Model* m_Model;
	int m_modelId;

	XMFLOAT3 m_front;

	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3* GetFront() { return &m_front; }
};
