#pragma once
#include "enemyState.h"

// �퓬���K�[�h�N���X
class EnemyStateCombatGuard :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;	// �^�C�}�[
public :
	EnemyStateCombatGuard(){}
	EnemyStateCombatGuard(class Enemy* pEnemy);
	void Update(class Enemy* pEnemy)override;
};