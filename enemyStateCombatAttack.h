#pragma once
#include "enemyState.h"

// �퓬���U���N���X
class EnemyStateCombatAttack :public EnemyStatePattern
{
private:
	float m_Timer = 0.0f;				// �^�C�}�[
	bool m_IsAttacking = false;			// �U������
	class OBB* m_ObbAttack = nullptr;	// �U������
	static class Audio* m_AttackSE;		// �U��SE
	static class Audio* m_GuardSE;		// �K�[�hSE
	static class Audio* m_RepelSE;		// �e��SE
public :
	EnemyStateCombatAttack() { Init(); }
	void Init();
	void Update(class Enemy* pEnemy)override;
	~EnemyStateCombatAttack();
};