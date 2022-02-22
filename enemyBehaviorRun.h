#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorRun : public ActionBase
{
private:
	static const float RUN_COMPLETE;	// 完了時間
public:
	// インスタンスゲッター
	static EnemyBehaviorRun* GetInstance()
	{
		static EnemyBehaviorRun instance;
		return &instance;
	}
	// 実行
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};