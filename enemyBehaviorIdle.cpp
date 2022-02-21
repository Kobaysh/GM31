#include "enemy.h"
#include "actionBase.h"
#include "enemyBehavior.h"
#include "enemyBehaviorIdle.h"

const float EnemyBehaviorIdle::IDLE_COMPLETE = 5.0f;

// ‘Ò‹@
ActionBase::EXE_STATE EnemyBehaviorIdle::Run(Enemy * pEnemy, EnemyBehavior* pBehavior)
{
	UNREFERENCED_PARAMETER(pEnemy);
	if (pBehavior->GetTimer() >= IDLE_COMPLETE)
	{
		pBehavior->ResetTimer();
		return EXE_STATE::COMPLETE;
	}

	return EXE_STATE::RUNNING;
}
