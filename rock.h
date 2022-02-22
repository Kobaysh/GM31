#pragma once
#include "gameObject.h"

class Rock : public GameObject
{
private:

//	Model* m_model;
	int m_modelId;
	class OBB* m_obb = nullptr;

	XMFLOAT3 m_front;

	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;


public:
	void Init();
	void Init(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3* GetFront() { return &m_front; }
	OBB& GetObb() { return *m_obb; }
};
