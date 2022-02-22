#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorLookingFor : public ActionBase
{
private:
	static const float LOOKINGFOR_COMPLETE;	// 完了時間
public:
	// インスタンスゲッター
	static EnemyBehaviorLookingFor* GetInstance()
	{
		static EnemyBehaviorLookingFor instance;
		return &instance;
	}
	// 実行
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};