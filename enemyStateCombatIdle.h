#pragma once
#include "enemyState.h"

class EnemyStateCombatIdle :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;
	static const float m_AttackInterval;
//	bool m_IsMissed = false;
public :
	void Update(class Enemy* pEnemy)override;
	EnemyStateCombatIdle(class Enemy* pEnemy);
	EnemyStateCombatIdle(){}
};