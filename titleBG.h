#pragma once
#include "gameObject.h"
class TitleBG : public GameObject
{
public:


	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;
};