#pragma once
#include "state.h"

class  EnemyState : public State
{
public:
	EnemyState():m_nowState(IDLE_IDLE), m_nextState(IDLE_IDLE),m_isAiStaterunning(false){}
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
private:
	En_Enemy_State m_nowState;
	En_Enemy_State m_nextState;

	bool m_isAiStaterunning;

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
	void Update()override;
	void ChangeState(En_Enemy_State newState);
	void UpdateAI();
	void SetAI();
	void AIMainRoutine();
};