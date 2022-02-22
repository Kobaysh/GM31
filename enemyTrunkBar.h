#pragma once
#include "gameObject.h"

// 体幹バークラス
class TrunkBar : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer;		// 頂点バッファ
	class Enemy* m_Enemy;				// 敵ポインター
public:
	void Init()override;
	void Init(class Enemy* pEnemy);
	void Uninit()override;
	void Update()override{}
	void Draw()override;

	// バー描画
	void Draw_Bar(XMFLOAT4 color, float perHP);
};