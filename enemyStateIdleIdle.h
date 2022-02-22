#pragma once
#include "enemyState.h"

// 待機中待機クラス
class EnemyStateIdleIdle : public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};