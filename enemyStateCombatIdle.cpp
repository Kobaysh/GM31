#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyStateCombatIdle.h"
#include "enemyStateCombatAttack.h"
#include "enemyStateCombatGuard.h"
#include "enemy.h"
#include "input.h"
#include "keylogger.h"
#include "utility.h"

const float EnemyStateCombatIdle::m_attackInterval = 10.0f;

void EnemyStateCombatIdle::Update(Enemy * pEnemy)
{
	Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
//	m_timer += 0.1f;
	if (KeyLogger_Trigger(KL_ATTACK))
	{
		// Šm—¦‚Å–hŒä
		if (Utility::Random(30))
		{
			EnemyStatePattern* pStatePattern = 
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatGuard);
			delete pStatePattern;
			return;
		}
	}

	if (m_timer > m_attackInterval)
	{
		// UŒ‚ŠJŽn
		EnemyStatePattern* pStatePattern = 
		pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatAttack);
		delete pStatePattern;
		return;
	}
}
