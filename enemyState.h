#pragma once
#include "state.h"

class  EnemyState : public State
{
public:
	EnemyState():m_nowState(IDLE_IDLE), m_nextState(IDLE_IDLE),m_isAiStaterunning(false){}
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
private:
	En_Enemy_State m_nowState;
	En_Enemy_State m_nextState;

	bool m_isAiStaterunning;

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
	void Update()override;
	void ChangeState(En_Enemy_State newState);
	void UpdateAI();
	void SetAI();
	void AIMainRoutine();
};