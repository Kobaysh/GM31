#pragma once
#include "enemyState.h"

class EnemyStateCombatGuard :public EnemyStatePattern
{
private:
	float m_timer = 0.0f;
	//static const float m_attackInterval;
public :
	EnemyStateCombatGuard(){}
	EnemyStateCombatGuard(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};