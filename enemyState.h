#pragma once
#include "state.h"

class  EnemyState : public State
{
public:
	EnemyState(){}
	~EnemyState(){}
	enum En_Enemy_State {
		NONE = -1,
// 待機
		IDLE_IDLE,
		IDLE_WALK,			// 散策
		IDLE_NINJAEXECUTION,// 忍殺
		IDLE_SURPRISE,		// 驚く
		IDLE_BEWARE,			// 警戒する
		IDLE_DISCOVER,		// 発見する
		IDLE_MOVE_TO_PLAYER,	// プレイヤーのもとに移動
// 戦闘
		COMBAT_IDLE,		// 待機
		COMBAT_ATTACK,		// 攻撃
		COMBAT_GUARD,		// ガード
		COMBAT_DAMAGED,		// ダメージを受ける
		COMBAT_NINJAEXECUTION,// 忍殺
		COMBAT_DEAD,		// 死亡
		MAX,
	};
private:
	En_Enemy_State m_nowState;
public:
	void Update()override;
	void ChangeState(En_Enemy_State newState);

};