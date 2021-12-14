#include "enemyStateCombatGuard.h"
#include "enemy.h"
#include "enemyStateCombatIdle.h"
#include "enemyStateCombatAttack.h"
#include "utility.h"


void EnemyStateCombatGuard::Update(Enemy * pEnemy)
{
	EnemyState* pState = pEnemy->GetEnemyState();
	m_timer += 0.1f;
	if (m_timer >= 10.0f)
	{
		// ƒK[ƒh‰ðœ
		pState->SetIsGuarding(false);
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateCombatIdle);
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
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateCombatAttack);
		delete pStatePattern;
		return;
	}
}
