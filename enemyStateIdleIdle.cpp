#include "enemyStateIdleIdle.h"
#include "Enemy.h"
#include "enemyStateIdleBeware.h"

void EnemyStateIdleIdle::Update(Enemy * pEnemy)
{
	EnemyStatePattern* pStatePattern = 
	pEnemy->GetEnemyState()->ChangeState(new EnemyStateIdleBeware);
	delete pStatePattern;
}
