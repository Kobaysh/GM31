#pragma once
#include "enemyState.h"

// 待機中警戒クラス
class EnemyStateIdleBeware :public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};