#pragma once

class Enemy;

class ActionBase
{
public:
	//	実行情報
	enum EXE_STATE
	{
		RUNNING,	// 実行中
		FAILED,		// 実行失敗
		COMPLETE,	// 実行成功
	};

	// 実行関数
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior) = 0;
};