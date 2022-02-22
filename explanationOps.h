#pragma once
#include "gameObject.h"

class ExplanationGame : public GameObject
{
private:
	class ExplaMove* m_explaMove;
	class ExplaAtk* m_explaAtk;
	class ExplaDef* m_explaDef;
	class ExplaLock* m_explaLock;
	class ExplaChange* m_explaChange;

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	
};