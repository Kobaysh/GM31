#pragma once
#include "enemyState.h"

// �퓬���ҋ@�N���X
class EnemyStateCombatIdle :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;					// �^�C�}�[
	static const float m_AttackInterval;	// �U���Ԋu
public :
	void Update(class Enemy* pEnemy)override;
	EnemyStateCombatIdle(class Enemy* pEnemy);
	EnemyStateCombatIdle(){}
};