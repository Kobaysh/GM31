#pragma once
#include "enemyState.h"

// �ҋ@���ҋ@�N���X
class EnemyStateIdleIdle : public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};