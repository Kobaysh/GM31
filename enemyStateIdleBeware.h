#pragma once
#include "enemyState.h"

// ‘Ò‹@’†Œx‰úƒNƒ‰ƒX
class EnemyStateIdleBeware :public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};