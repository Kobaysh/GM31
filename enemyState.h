#pragma once
#include "state.h"

class  EnemyState : public State
{
public:
	EnemyState():m_nowState(IDLE_IDLE), m_nextState(IDLE_IDLE),m_isAiStaterunning(false){}
	~EnemyState(){}
	enum En_Enemy_State {
		NONE = -1,
// ‘Ò‹@
		IDLE_IDLE,
		IDLE_WALK,				// Uô
		IDLE_NINJAEXECUTION,	// ”EE
		IDLE_SURPRISE,			// ‹Á‚­
		IDLE_BEWARE,			// Œx‰ú‚·‚é
		IDLE_DISCOVER,			// ”­Œ©‚·‚é
		IDLE_MOVE_TO_PLAYER,	// ƒvƒŒƒCƒ„[‚Ì‚à‚Æ‚ÉˆÚ“®
// í“¬
		COMBAT_IDLE,			// ‘Ò‹@
		COMBAT_ATTACK,			// UŒ‚
		COMBAT_GUARD,			// ƒK[ƒh
		COMBAT_DAMAGED,			// ƒ_ƒ[ƒW‚ğó‚¯‚é
		COMBAT_NINJAEXECUTION,	// ”EE
		COMBAT_DEAD,			// €–S
		MAX,
	};
private:
	En_Enemy_State m_nowState;
	En_Enemy_State m_nextState;

	bool m_isAiStaterunning;

	void Idle_Idle();
	void Idle_Walk();				// Uô
	void Idle_NinjaExcution();	// ”EE
	void Idle_Surprize();			// ‹Á‚­
	void Idle_Beware();			// Œx‰ú‚·‚é
	void Idle_Discover();			// ”­Œ©‚·‚é
	void Idle_MoveToPlayer();	// ƒvƒŒƒCƒ„[‚Ì‚à‚Æ‚ÉˆÚ“®

	void Combat_Idle();			// ‘Ò‹@
	void Combat_Attack();			// UŒ‚
	void Combat_Guard();		// ƒK[ƒh
	void Combat_Damaged();			// ƒ_ƒ[ƒW‚ğó‚¯‚é
	void Combat_Ninjaexecution();	// ”EE
	void Combat_Dead();			// €–S
public:
	void Update()override;
	void ChangeState(En_Enemy_State newState);
	void UpdateAI();
	void SetAI();
	void AIMainRoutine();
};