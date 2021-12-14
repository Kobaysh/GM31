#pragma once
#include "enemyState.h"

class EnemyStateIdleBeware :public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};