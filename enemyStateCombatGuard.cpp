#include "enemyStateCombatGuard.h"
#include "enemy.h"
#include "enemyStateCombatIdle.h"
#include "enemyStateCombatAttack.h"
#include "utility.h"


EnemyStateCombatGuard::EnemyStateCombatGuard(Enemy * pEnemy)
{
	pEnemy->SetAnimationName("guard");
}

void EnemyStateCombatGuard::Update(Enemy * pEnemy)
{
	EnemyState* pState = pEnemy->GetEnemyState();
	m_timer += 0.1f;
	if (m_timer >= 10.0f)
	{
		// ƒK[ƒh‰ðœ
		pState->SetIsGuarding(false);
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateCombatIdle(pEnemy));
		pState->SetStateName("EnemyStateCombatIdle");
		delete pStatePattern;
		return;
	}
	bool isRepel = false;
	// ƒvƒŒƒCƒ„[‚ÌUŒ‚‚ðŠm—¦‚Å’e‚­
	if (pState->GetIsCollided())
	{
		pState->SetIsCollided(false);
		isRepel = Utility::Random(30);
	}
	// ’e‚¢‚½‚çUŒ‚
	if (isRepel)
	{
		pState->SetIsGuarding(false);
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateCombatAttack);
		pState->SetStateName("EnemyStateCombatAttack");
		delete pStatePattern;
		return;
	}
}
