#pragma once
#include "state.h"

class  EnemyState : public State
{
public:
	EnemyState(){}
	~EnemyState(){}
	enum En_Enemy_State {
		NONE = -1,
		IDLE,
		CROUCH,
		DEAD,
		WALK,
		CROUCHWALK,
		RUN,
		JUMP,
		MAX,
	};
private:
	En_Enemy_State m_nowState;
public:
	void Update();
	void ChangeState(En_Enemy_State newState);

};