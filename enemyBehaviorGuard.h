#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorGuard : public ActionBase
{
private:
	static const float GUARD_COMPLETE;	// 完了時間
public:
	// インスタンスゲッター
	static EnemyBehaviorGuard* GetInstance()
	{
		static EnemyBehaviorGuard instance;
		return &instance;
	}
	// 実行
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};