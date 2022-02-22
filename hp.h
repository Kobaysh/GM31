#pragma once
#include "gameObject.h"

// 敵HPバークラス
class HpBar : public GameObject
{
private:	
	int m_NowHP;					// 現在HP
	int m_MaxHP;					// 最大HP
	ID3D11Buffer* m_VertexBuffer;	// 頂点バッファ
public:
	void Init()override;
	void Init(XMFLOAT3 pos, XMFLOAT3 scale, int nowHP, int maxHP);
	void Uninit()override;
	void Update()override{}
	void Draw()override;
	void Draw_Bar(XMFLOAT4 color, float perHP);
	void SetHP(int nowHp, int maxHP) { m_NowHP = nowHp, m_MaxHP = maxHP; }
};