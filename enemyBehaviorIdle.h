#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorIdle : public ActionBase
{
private:
	static const float IDLE_COMPLETE;
public:
	static EnemyBehaviorIdle* GetInstance()
	{
		static EnemyBehaviorIdle instance;
		return &instance;
	}
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};