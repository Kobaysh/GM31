#pragma once
#include "enemyState.h"

// í“¬’†UŒ‚ƒNƒ‰ƒX
class EnemyStateCombatAttack :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;				// ƒ^ƒCƒ}[
	bool m_IsAttacking = false;			// UŒ‚’†‚©
	class OBB* m_ObbAttack = nullptr;	// UŒ‚”»’è
	static class Audio* m_AttackSE;		// UŒ‚SE
	static class Audio* m_GuardSE;		// ƒK[ƒhSE
	static class Audio* m_RepelSE;		// ’e‚«SE
public :
	EnemyStateCombatAttack() { Init(); }
	void Init();
	void Update(class Enemy* pEnemy)override;
	~EnemyStateCombatAttack();
};