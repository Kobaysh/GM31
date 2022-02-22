#pragma once
#include "enemyState.h"

// 戦闘中被ダメージクラス
class EnemyStateCombatDamaged :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;	// タイマー
public :
	EnemyStateCombatDamaged(){}
	EnemyStateCombatDamaged(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};