#pragma once
#include "enemyState.h"

class EnemyStateCombatGuard :public EnemyStatePattern
{
private:
	//float m_timer = 0.0f;
	//static const float m_attackInterval;
public :
	void Update(class Enemy* pEnemy)override;
};