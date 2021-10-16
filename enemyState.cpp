#include "enemyState.h"

void EnemyState::Update()
{
	UpdateAI();
}

void EnemyState::ChangeState(En_Enemy_State newState)
{
    m_nowState = newState;
}

void EnemyState::SetAI()
{
	AIMainRoutine();
	if (m_isAiStaterunning) return;
	if (m_nowState != m_nextState) {
		m_nowState = m_nextState;
	}
}

void EnemyState::AIMainRoutine()
{

}

void EnemyState::UpdateAI()
{
	SetAI();

	switch (m_nowState)
	{
	case EnemyState::NONE:
		break;
	case EnemyState::IDLE_IDLE:
		Idle_Idle();
		break;
	case EnemyState::IDLE_WALK:
		Idle_Walk();
		break;
	case EnemyState::IDLE_NINJAEXECUTION:
		break;
	case EnemyState::IDLE_SURPRISE:
		break;
	case EnemyState::IDLE_BEWARE:
		break;
	case EnemyState::IDLE_DISCOVER:
		break;
	case EnemyState::IDLE_MOVE_TO_PLAYER:
		break;
	case EnemyState::COMBAT_IDLE:
		break;
	case EnemyState::COMBAT_ATTACK:
		break;
	case EnemyState::COMBAT_GUARD:
		break;
	case EnemyState::COMBAT_DAMAGED:
		break;
	case EnemyState::COMBAT_NINJAEXECUTION:
		break;
	case EnemyState::COMBAT_DEAD:
		break;
	case EnemyState::MAX:
		break;
	default:
		break;
	}
}

void EnemyState::Idle_Idle()
{
}

void EnemyState::Idle_Walk()
{
}

void EnemyState::Idle_NinjaExcution()
{
}

void EnemyState::Idle_Surprize()
{
}

void EnemyState::Idle_Beware()
{
}

void EnemyState::Idle_Discover()
{
}

void EnemyState::Idle_MoveToPlayer()
{
}

void EnemyState::Combat_Idle()
{
}

void EnemyState::Combat_Attack()
{
}

void EnemyState::Combat_Guard()
{
}

void EnemyState::Combat_Damaged()
{
}

void EnemyState::Combat_Ninjaexecution()
{
}

void EnemyState::Combat_Dead()
{
}
