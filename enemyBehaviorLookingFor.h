#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorLookingFor : public ActionBase
{
private:
	static const float LOOKINGFOR_COMPLETE;	// ��������
public:
	// �C���X�^���X�Q�b�^�[
	static EnemyBehaviorLookingFor* GetInstance()
	{
		static EnemyBehaviorLookingFor instance;
		return &instance;
	}
	// ���s
	virtual EXE_STATE Run(Enemy* pEnemy, class EnemyBehavior* pBehavior)override;
};