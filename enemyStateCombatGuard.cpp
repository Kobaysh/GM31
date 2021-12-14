#include "enemyStateCombatGuard.h"
#include "enemy.h"
#include "enemyStateCombatIdle.h"


void EnemyStateCombatGuard::Update(Enemy * pEnemy)
{
	m_timer += 0.1f;
	if (m_timer >= 10.0f)
	{
		// ƒK[ƒh‰ðœ
		pEnemy->GetEnemyState()->SetIsGuarding(false);
		EnemyStatePattern* pStatePattern = 
		pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle);
		delete pStatePattern;
	}
}
