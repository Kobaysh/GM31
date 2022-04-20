#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorGuard : public ActionBase
{
private:
	static const float GUARD_COMPLETE;	// ��������
public:
	// �C���X�^���X�Q�b�^�[
	static EnemyBehaviorGuard* GetInstance()
	{
		static EnemyBehaviorGuard instance;
		return &instance;
	}
	// ���s
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};