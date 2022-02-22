#pragma once
#include "gameObject.h"

class ExplanationGame : public GameObject
{
private:
	class ExplaMove* m_ExplaMove;		// 移動説明オブジェクト 
	class ExplaAtk* m_ExplaAtk;			// 攻撃説明オブジェクト
	class ExplaDef* m_ExplaDef;			// 防御説明オブジェクト
	class ExplaLock* m_ExplaLock;		// 固定説明オブジェクト
	class ExplaChange* m_ExplaChange;	// 切替説明オブジェクト

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	
};