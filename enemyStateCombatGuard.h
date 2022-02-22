#pragma once
#include "enemyState.h"

class EnemyStateCombatGuard :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;
	//static const float m_AttackInterval;
public :
	EnemyStateCombatGuard(){}
	EnemyStateCombatGuard(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};