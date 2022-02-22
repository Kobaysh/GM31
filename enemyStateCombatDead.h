#pragma once
#include "enemyState.h"

// 戦闘中死亡クラス
class EnemyStateCombatDead :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;	// タイマー
public :
	EnemyStateCombatDead(){}
	EnemyStateCombatDead(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};