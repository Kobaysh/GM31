#pragma once
#include "enemyState.h"

// 戦闘中待機クラス
class EnemyStateCombatIdle :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;					// タイマー
	static const float m_AttackInterval;	// 攻撃間隔
public :
	void Update(class Enemy* pEnemy)override;
	EnemyStateCombatIdle(class Enemy* pEnemy);
	EnemyStateCombatIdle(){}
};