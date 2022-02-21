#pragma once
#include "enemyState.h"

class EnemyStateCombatAttack :public EnemyStatePattern
{
private:
	float m_timer = 0.0f;
	//static const float m_attackInterval;
	bool m_isAttacking = false;
	class OBB* m_obbAttack = nullptr;
	static class Audio* m_attackSE;
	static class Audio* m_guardSE;
	static class Audio* m_repelSE;
public :
	EnemyStateCombatAttack() { Init(); }
	void Init();
	void Update(class Enemy* pEnemy)override;
	~EnemyStateCombatAttack();
};