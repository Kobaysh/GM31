#pragma once
#include "enemyState.h"

// �퓬�����S�N���X
class EnemyStateCombatDead :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;	// �^�C�}�[
public :
	EnemyStateCombatDead(){}
	EnemyStateCombatDead(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};