#pragma once
#include "state.h"
//#include "enemy.h"

class EnemyStatePattern : public State
{
protected:
	class Enemy* m_enemy;
};

class  EnemyState : public State
{
public:
	EnemyState() = delete;
	EnemyState(Enemy* enemy):m_nowState(IDLE_IDLE), m_nextState(IDLE_IDLE),m_isAiStaterunning(false),m_enemy(enemy)
	{
	//	m_radiusDiscoverPlayer = 0.0f;
		m_timer = 0.0f;
	}
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
	static const char* enumChar_Enemy_State[En_Enemy_State::MAX]; 
	//{
	//	"IDLE_IDLE",
	//	"IDLE_WALK",				// Uô
	//	"IDLE_NINJAEXECUTION",	// ”EE
	//	"IDLE_SURPRISE",			// ‹Á‚­
	//	"IDLE_BEWARE",			// Œx‰ú‚·‚é
	//	"IDLE_DISCOVER",			// ”­Œ©‚·‚é
	//	"IDLE_MOVE_TO_PLAYER",	// ƒvƒŒƒCƒ„[‚Ì‚à‚Æ‚ÉˆÚ“®
	//							// í“¬
	//	"COMBAT_IDLE",			// ‘Ò‹@
	//	"COMBAT_ATTACK",			// UŒ‚
	//	"COMBAT_GUARD",			// ƒK[ƒh
	//	"COMBAT_DAMAGED",			// ƒ_ƒ[ƒW‚ğó‚¯‚é
	//	"COMBAT_NINJAEXECUTION",	// ”EE
	//	"COMBAT_DEAD",			// €–S
	//};
private:

	class Enemy* m_enemy;
	En_Enemy_State m_nowState;
	En_Enemy_State m_nextState;

//	void* m_pStateData;
	//Enemy::EnemyStateData* m_pStateData;
//	float m_radiusDiscoverPlayer;
	float m_timer;

	bool m_isAiStaterunning;

	void UpdateAI();
	void SetAI();
	void AIMainRoutine();

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
	//void Init(float radDiscPlayer);
	//void Init(Enemy::EnemyStateData stateData);
	//void Init(void* stateData);
	//void Init(void* stateData);
	//void Init(Enemy::EnemyStateData* stateData);
	void Update()override;
	void ChangeState(En_Enemy_State newState);
	En_Enemy_State GetNowState() { return m_nowState; }
};