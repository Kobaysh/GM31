#pragma once
#include "enemyState.h"

class EnemyStateIdleDiscover :public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};