#pragma once

#include "actionBase.h"

class Enemy;

class EnemyBehaviorLookingFor : ActionBase
{
private:
	float m_timer = 0.0f;
	static const float LOOKINGFOR_COMPLETE;
public:
	virtual EXE_STATE Run(Enemy* pEnemy)override;
};