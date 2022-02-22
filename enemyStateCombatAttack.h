#pragma once
#include "enemyState.h"

class EnemyStateCombatAttack :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;
	//static const float m_AttackInterval;
	bool m_IsAttacking = false;
	class OBB* m_ObbAttack = nullptr;
	static class Audio* m_AttackSE;
	static class Audio* m_GuardSE;
	static class Audio* m_RepelSE;
public :
	EnemyStateCombatAttack() { Init(); }
	void Init();
	void Update(class Enemy* pEnemy)override;
	~EnemyStateCombatAttack();
};