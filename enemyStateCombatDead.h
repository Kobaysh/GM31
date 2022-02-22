#pragma once
#include "enemyState.h"

class EnemyStateCombatDead :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;
	//static const float m_AttackInterval;
public :
	EnemyStateCombatDead(){}
	EnemyStateCombatDead(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};