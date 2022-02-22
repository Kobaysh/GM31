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

	// ���s�֐�
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior) = 0;
};