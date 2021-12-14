#pragma once
#include "enemyState.h"

class EnemyStateIdleIdle : public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};