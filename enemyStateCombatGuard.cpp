#include "enemyStateCombatGuard.h"
#include "enemy.h"
#include "enemyStateCombatIdle.h"
#include "enemyStateCombatAttack.h"
#include "utility.h"


void EnemyStateCombatGuard::Update(Enemy * pEnemy)
{
	EnemyState* pState = pEnemy->GetEnemyState();
	m_timer += 0.1f;
	if (m_timer >= 10.0f)
	{
		// �K�[�h����
		pState->SetIsGuarding(false);
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateCombatIdle);
		delete pStatePattern;
		return;
	}
	bool isRepel = false;
	// �v���C���[�̍U�����m���Œe��
	if (pState->GetIsCollided())
	{
		pState->SetIsCollided(false);
		isRepel = Utility::Random(30);
	}
	// �e������U��
	if (isRepel)
	{
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateCombatAttack);
		delete pStatePattern;
		return;
	}
}
