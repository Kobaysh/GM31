#pragma once
#include "state.h"

class PlayerState : public State
{
public:
	PlayerState(){}
	~PlayerState(){}
	enum En_Player_State {
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
	En_Player_State m_nowState;
public:
	void Update();
	void ChangeState(En_Player_State newState);
};

