#pragma once
#include "enemyState.h"

// ‘Ò‹@’†”­Œ©ƒNƒ‰ƒX
class EnemyStateIdleDiscover :public EnemyStatePattern
{
public :
	EnemyStateIdleDiscover(){}
	EnemyStateIdleDiscover(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};