#pragma once
#include "enemyState.h"

class EnemyStateCombatIdle :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;
	static const float m_attackInterval;
//	bool m_isMissed = false;
public :
	void Update(class Enemy* pEnemy)override;
	EnemyStateCombatIdle(class Enemy* pEnemy);
	EnemyStateCombatIdle(){}
};