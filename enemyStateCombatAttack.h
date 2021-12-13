#pragma once
#include "enemyState.h"

class EnemyStateCombatAttack :public EnemyStatePattern
{
private:
	float m_timer = 0.0f;
	//static const float m_attackInterval;
	bool m_isAttacking = false;
	class OBB* m_obbAttack = nullptr;
public :
	void Update(class Enemy* pEnemy)override;
	~EnemyStateCombatAttack();
};