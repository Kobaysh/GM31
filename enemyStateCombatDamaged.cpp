#include "enemyStateCombatDamaged.h"
#include "enemyStateCombatDead.h"
#include "enemyStateCombatIdle.h"
#include "enemy.h"
EnemyStateCombatDamaged::EnemyStateCombatDamaged(Enemy * pEnemy)
{
	pEnemy->SetAnimationName("hit_reaction");
}

void EnemyStateCombatDamaged::Update(Enemy * pEnemy)
{
	if (pEnemy->GetNowHp() <= 0)
	{
		EnemyStatePattern* pStatePattern =
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatDead(pEnemy));
		pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatDead");
		delete pStatePattern;
		return;
	}

	m_Timer += 0.1f;

	if (m_Timer >= 5.0f)
	{
		EnemyStatePattern* pStatePattern =
		pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle(pEnemy));
		pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatIdle");
		delete pStatePattern;
		return;
	}
}
