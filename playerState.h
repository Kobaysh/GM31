#pragma once
class PlayerState
{
public:
	PlayerState(){}
	~PlayerState(){}
	enum Player_State {
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
	Player_State m_nowState;
public:
	void Update();
	void ChangeState(PlayerState newState);
};

