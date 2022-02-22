#pragma once
#include "gameObject.h"

class Rock : public GameObject
{
private:

//	Model* m_Model;
	int m_ModelId;
	class OBB* m_Obb = nullptr;

	XMFLOAT3 m_Front;

	static ID3D11VertexShader* m_VertexShader;
	static ID3D11PixelShader* m_PixelShader;
	static ID3D11InputLayout* m_VertexLayout;


public:
	void Init();
	void Init(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3* GetFront() { return &m_Front; }
	OBB& GetObb() { return *m_Obb; }
};
