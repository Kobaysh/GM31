#pragma once
#include "enemyState.h"

// �ҋ@���x���N���X
class EnemyStateIdleBeware :public EnemyStatePattern
{
public :
	void Update(class Enemy* pEnemy)override;
};