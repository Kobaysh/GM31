#pragma once
#include "enemyState.h"

// 戦闘中ガードクラス
class EnemyStateCombatGuard :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;	// タイマー
public :
	EnemyStateCombatGuard(){}
	EnemyStateCombatGuard(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};