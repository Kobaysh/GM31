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
// �ҋ@
		IDLE_IDLE,
		IDLE_WALK,				// �U��
		IDLE_NINJAEXECUTION,	// �E�E
		IDLE_SURPRISE,			// ����
		IDLE_BEWARE,			// �x������
		IDLE_DISCOVER,			// ��������
		IDLE_MOVE_TO_PLAYER,	// �v���C���[�̂��ƂɈړ�
// �퓬
		COMBAT_IDLE,			// �ҋ@
		COMBAT_ATTACK,			// �U��
		COMBAT_GUARD,			// �K�[�h
		COMBAT_DAMAGED,			// �_���[�W���󂯂�
		COMBAT_NINJAEXECUTION,	// �E�E
		COMBAT_DEAD,			// ���S
		MAX,
	};
	static const char* enumChar_Enemy_State[En_Enemy_State::MAX]; 
	//{
	//	"IDLE_IDLE",
	//	"IDLE_WALK",				// �U��
	//	"IDLE_NINJAEXECUTION",	// �E�E
	//	"IDLE_SURPRISE",			// ����
	//	"IDLE_BEWARE",			// �x������
	//	"IDLE_DISCOVER",			// ��������
	//	"IDLE_MOVE_TO_PLAYER",	// �v���C���[�̂��ƂɈړ�
	//							// �퓬
	//	"COMBAT_IDLE",			// �ҋ@
	//	"COMBAT_ATTACK",			// �U��
	//	"COMBAT_GUARD",			// �K�[�h
	//	"COMBAT_DAMAGED",			// �_���[�W���󂯂�
	//	"COMBAT_NINJAEXECUTION",	// �E�E
	//	"COMBAT_DEAD",			// ���S
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
	void Idle_Walk();				// �U��
	void Idle_NinjaExcution();	// �E�E
	void Idle_Surprize();			// ����
	void Idle_Beware();			// �x������
	void Idle_Discover();			// ��������
	void Idle_MoveToPlayer();	// �v���C���[�̂��ƂɈړ�

	void Combat_Idle();			// �ҋ@
	void Combat_Attack();			// �U��
	void Combat_Guard();		// �K�[�h
	void Combat_Damaged();			// �_���[�W���󂯂�
	void Combat_Ninjaexecution();	// �E�E
	void Combat_Dead();			// ���S
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