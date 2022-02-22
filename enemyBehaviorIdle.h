#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorIdle : public ActionBase
{
private:
	static const float IDLE_COMPLETE;	// 完了時間
public:
	// インスタンスゲッター
	static EnemyBehaviorIdle* GetInstance()
	{
		static EnemyBehaviorIdle instance;
		return &instance;
	}
	// 実行
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};