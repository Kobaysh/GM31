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

	virtual EXE_STATE Run(Enemy* pEnemy) = 0;
	static const float UPDATE_TIMER_AMOUNT;	// updateで増やすタイマーの量
};

const float ActionBase::UPDATE_TIMER_AMOUNT = 0.01f; // updateで増やすタイマーの量