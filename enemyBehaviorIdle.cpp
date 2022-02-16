#include "enemy.h"
#include "actionBase.h"
#include "enemyBehaviorIdle.h"

const float EnemyBehaviorIdle::IDLE_COMPLETE = 5.0f;

// ‘Ò‹@
ActionBase::EXE_STATE EnemyBehaviorIdle::Run(Enemy * pEnemy)
{

	m_timer += UPDATE_TIMER_AMOUNT;

	if (m_timer >= IDLE_COMPLETE)
	{
		return EXE_STATE::COMPLETE;
	}

	return EXE_STATE::RUNNING;
}
