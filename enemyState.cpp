#include "enemyState.h"

void EnemyState::Update()
{
    
}

void EnemyState::ChangeState(En_Enemy_State newState)
{
    m_nowState = newState;
}
