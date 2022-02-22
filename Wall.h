#pragma once
#include "gameObject.h"
class Wall : public GameObject
{
private:
	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;
	class OBB* m_Obb = nullptr;
	int m_ModelId;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

