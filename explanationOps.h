#pragma once
#include "gameObject.h"

class ExplanationGame : public GameObject
{
private:
	class ExplaMove* m_ExplaMove;
	class ExplaAtk* m_ExplaAtk;
	class ExplaDef* m_ExplaDef;
	class ExplaLock* m_ExplaLock;
	class ExplaChange* m_ExplaChange;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	
};