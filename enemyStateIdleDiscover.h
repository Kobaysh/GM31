#pragma once
#include "enemyState.h"

// 待機中発見クラス
class EnemyStateIdleDiscover :public EnemyStatePattern
{
public :
	EnemyStateIdleDiscover(){}
	EnemyStateIdleDiscover(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};