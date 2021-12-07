#pragma once
#include "state.h"
#include "enemy.h"

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
// 待機
		IDLE_IDLE,
		IDLE_WALK,				// 散策
		IDLE_NINJAEXECUTION,	// 忍殺
		IDLE_SURPRISE,			// 驚く
		IDLE_BEWARE,			// 警戒する
		IDLE_DISCOVER,			// 発見する
		IDLE_MOVE_TO_PLAYER,	// プレイヤーのもとに移動
// 戦闘
		COMBAT_IDLE,			// 待機
		COMBAT_ATTACK,			// 攻撃
		COMBAT_GUARD,			// ガード
		COMBAT_DAMAGED,			// ダメージを受ける
		COMBAT_NINJAEXECUTION,	// 忍殺
		COMBAT_DEAD,			// 死亡
		MAX,
	};
	static const char* enumChar_Enemy_State[En_Enemy_State::MAX]; 
	//{
	//	"IDLE_IDLE",
	//	"IDLE_WALK",				// 散策
	//	"IDLE_NINJAEXECUTION",	// 忍殺
	//	"IDLE_SURPRISE",			// 驚く
	//	"IDLE_BEWARE",			// 警戒する
	//	"IDLE_DISCOVER",			// 発見する
	//	"IDLE_MOVE_TO_PLAYER",	// プレイヤーのもとに移動
	//							// 戦闘
	//	"COMBAT_IDLE",			// 待機
	//	"COMBAT_ATTACK",			// 攻撃
	//	"COMBAT_GUARD",			// ガード
	//	"COMBAT_DAMAGED",			// ダメージを受ける
	//	"COMBAT_NINJAEXECUTION",	// 忍殺
	//	"COMBAT_DEAD",			// 死亡
	//};
private:

	Enemy* m_enemy;
	En_Enemy_State m_nowState;
	En_Enemy_State m_nextState;

	Enemy::EnemyStateData* m_pStateData;
//	float m_radiusDiscoverPlayer;
	float m_timer;

	bool m_isAiStaterunning;

	void UpdateAI();
	void SetAI();
	void AIMainRoutine();

	void Idle_Idle();
	void Idle_Walk();				// 散策
	void Idle_NinjaExcution();	// 忍殺
	void Idle_Surprize();			// 驚く
	void Idle_Beware();			// 警戒する
	void Idle_Discover();			// 発見する
	void Idle_MoveToPlayer();	// プレイヤーのもとに移動

	void Combat_Idle();			// 待機
	void Combat_Attack();			// 攻撃
	void Combat_Guard();		// ガード
	void Combat_Damaged();			// ダメージを受ける
	void Combat_Ninjaexecution();	// 忍殺
	void Combat_Dead();			// 死亡
public:
	//void Init(float radDiscPlayer);
	//void Init(Enemy::EnemyStateData stateData);
	void Init(Enemy::EnemyStateData* stateData);
	void Update()override;
	void ChangeState(En_Enemy_State newState);
	En_Enemy_State GetNowState() { return m_nowState; }
};