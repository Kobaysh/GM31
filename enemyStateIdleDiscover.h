#pragma once
#include "enemyState.h"

// �ҋ@�������N���X
class EnemyStateIdleDiscover :public EnemyStatePattern
{
public :
	EnemyStateIdleDiscover(){}
	EnemyStateIdleDiscover(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};