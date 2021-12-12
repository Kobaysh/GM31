#pragma once
#include "enemyState.h"

class EnemyStateCombatIdle :public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};