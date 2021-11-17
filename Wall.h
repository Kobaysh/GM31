#pragma once
#include "gameObject.h"
class Wall : public GameObject
{
private:
	ID3D11Buffer*				m_vertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_texture = NULL;
	class OBB* m_obb = nullptr;
	int m_modelId;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

