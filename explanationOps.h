#pragma once
#include "gameObject.h"

class ExplanationGame : public GameObject
{
private:
	class ExplaMove* m_ExplaMove;		// �ړ������I�u�W�F�N�g 
	class ExplaAtk* m_ExplaAtk;			// �U�������I�u�W�F�N�g
	class ExplaDef* m_ExplaDef;			// �h������I�u�W�F�N�g
	class ExplaLock* m_ExplaLock;		// �Œ�����I�u�W�F�N�g
	class ExplaChange* m_ExplaChange;	// �ؑ֐����I�u�W�F�N�g

public:
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	
};