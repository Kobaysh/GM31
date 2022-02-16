#pragma once

class Enemy;

class ActionBase
{
public:
	//	���s���
	enum EXE_STATE
	{
		RUNNING,	// ���s��
		FAILED,		// ���s���s
		COMPLETE,	// ���s����
	};

	virtual EXE_STATE Run(Enemy* pEnemy) = 0;
	static const float UPDATE_TIMER_AMOUNT;	// update�ő��₷�^�C�}�[�̗�
};

const float ActionBase::UPDATE_TIMER_AMOUNT = 0.01f; // update�ő��₷�^�C�}�[�̗�