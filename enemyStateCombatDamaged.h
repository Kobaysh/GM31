#pragma once
#include "enemyState.h"

// �퓬����_���[�W�N���X
class EnemyStateCombatDamaged :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;	// �^�C�}�[
public :
	EnemyStateCombatDamaged(){}
	EnemyStateCombatDamaged(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};