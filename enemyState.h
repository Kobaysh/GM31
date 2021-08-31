#pragma once
#include "state.h"

class  EnemyState : public State
{
public:
	EnemyState(){}
	~EnemyState(){}
	enum En_Enemy_State {
		NONE = -1,
// �ҋ@
		IDLE_IDLE,
		IDLE_WALK,			// �U��
		IDLE_NINJAEXECUTION,// �E�E
		IDLE_SURPRISE,		// ����
		IDLE_BEWARE,			// �x������
		IDLE_DISCOVER,		// ��������
		IDLE_MOVE_TO_PLAYER,	// �v���C���[�̂��ƂɈړ�
// �퓬
		COMBAT_IDLE,		// �ҋ@
		COMBAT_ATTACK,		// �U��
		COMBAT_GUARD,		// �K�[�h
		COMBAT_DAMAGED,		// �_���[�W���󂯂�
		COMBAT_NINJAEXECUTION,// �E�E
		COMBAT_DEAD,		// ���S
		MAX,
	};
private:
	En_Enemy_State m_nowState;
public:
	void Update()override;
	void ChangeState(En_Enemy_State newState);

};