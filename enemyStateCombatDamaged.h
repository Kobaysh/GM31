#pragma once
#include "enemyState.h"

class EnemyStateCombatDamaged :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;
	//static const float m_AttackInterval;
public :
	EnemyStateCombatDamaged(){}
	EnemyStateCombatDamaged(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};