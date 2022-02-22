#pragma once
#include "gameObject.h"
class TrunkBar : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;
	class Enemy* m_pEnemy;
public:
	void Init()override;
	void Init(class Enemy* pEnemy);
	void Uninit()override;
	void Update()override{}
	void Draw()override;
	void Draw_Bar(XMFLOAT4 color, float perHP);
};