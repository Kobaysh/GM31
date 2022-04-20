#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"
#include "actionBase.h"
#include "enemyBehavior.h"
#include "enemyBehaviorGuard.h"

const float EnemyBehaviorGuard::GUARD_COMPLETE = 3.0f;	// Š®—¹ŽžŠÔ

#define NEARLY_ZERO_VALUE 0.001f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.012f)

// ‘–‚é
ActionBase::EXE_STATE EnemyBehaviorGuard::Run(Enemy * pEnemy,  EnemyBehavior* pBehavior)
{


	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player)
	{
		pBehavior->ResetTimer();
		return EXE_STATE::FAILED;
	}


	if (pBehavior->GetTimer() >= GUARD_COMPLETE)
	{
		pBehavior->ResetTimer();
		return EXE_STATE::FAILED;
	}
	return EXE_STATE::RUNNING;
}
