#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorRun : public ActionBase
{
private:
	static const float RUN_COMPLETE;	// ��������
public:
	// �C���X�^���X�Q�b�^�[
	static EnemyBehaviorRun* GetInstance()
	{
		static EnemyBehaviorRun instance;
		return &instance;
	}
	// ���s
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};