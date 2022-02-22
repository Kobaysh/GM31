#include "enemyState.h"
#include "enemy.h"
#include "enemyStateIdleIdle.h"


EnemyState::EnemyState():m_StatePattern(new EnemyStateIdleIdle)
{
	
}

EnemyState::~EnemyState()
{
	if (m_StatePattern)
	{
		delete m_StatePattern;
		m_StatePattern = nullptr;
	}
}

void EnemyState::Update(Enemy * pEnemy)
{
	m_StatePattern->Update(pEnemy);
}

EnemyStatePattern * EnemyState::ChangeState(EnemyStatePattern * pStatePattern)
{
	EnemyStatePattern* temp = m_StatePattern;
	m_StatePattern = pStatePattern;
	return temp;
}
