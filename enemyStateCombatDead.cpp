#include "enemyStateCombatDead.h"
#include "enemy.h"

EnemyStateCombatDead::EnemyStateCombatDead(Enemy * pEnemy)
{
	pEnemy->SetAnimationName("dying");
}

void EnemyStateCombatDead::Update(Enemy * pEnemy)
{
	// �A�j���[�V�������I����������
	m_timer += 0.1f;
	if (m_timer >= 20.0f)
	{
		pEnemy->SetDead();
	}
}
