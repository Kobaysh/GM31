#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemyStateCombatIdle.h"
#include "enemyStateCombatAttack.h"
#include "enemyStateCombatGuard.h"
#include "enemyStateCombatDamaged.h"
#include "enemyStateIdleDiscover.h"
#include "enemy.h"
#include "input.h"
#include "keylogger.h"
#include "utility.h"

const float EnemyStateCombatIdle::m_AttackInterval = 10.0f;

void EnemyStateCombatIdle::Update(Enemy * pEnemy)
{
	Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!pPlayer) return;
	EnemyState* pState = pEnemy->GetEnemyState();
	m_Timer += 0.1f;
	XMVECTOR vPlayerPos, vEnemyPos, vToPlayer, vLength;
	float length;
	vPlayerPos = XMLoadFloat3(&pPlayer->GetPosition());
	vEnemyPos = XMLoadFloat3(&pEnemy->GetPosition());
	vToPlayer = vPlayerPos - vEnemyPos;
	//	vToPlayer.m128_f32[1] = 0.0f;
	vLength = XMVector3Length(vToPlayer);
	XMStoreFloat(&length, vLength);
	// プレイヤーが離れたら追いかける
	if (pEnemy->GetEnemyStateData()->m_CombatRad * 2 <= length)
	{
		pEnemy->SetMoveVector(XMFLOAT3(0.0f, 0.0f, 0.0f));
		EnemyStatePattern* pStatePattern = 
			pState->ChangeState(new EnemyStateIdleDiscover(pEnemy));
		pState->SetStateName("EnemyStateIdleDiscover");
		delete pStatePattern;
		return;
	}
	// 視界より遠ざかったら見失う

	if (KeyLogger_Trigger(KL_ATTACK))
	{
		// 確率で防御
		if (Utility::Random(30))
		{
			pState->SetIsGuarding(true);
			EnemyStatePattern* pStatePattern =
				pState->ChangeState(new EnemyStateCombatGuard(pEnemy));
			pState->SetStateName("EnemyStateCombatGuard");
			delete pStatePattern;
			return;
		}
	}

	if (m_Timer > m_AttackInterval)
	{
		// 攻撃開始
		EnemyStatePattern* pStatePattern =
			pState->ChangeState(new EnemyStateCombatAttack);
		pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatAttack");
		delete pStatePattern;
		return;
	}

	if (pState->GetIsDamaged())
	{
		// 攻撃をくらったら
		EnemyStatePattern* pStatePattern =
			pState->ChangeState(new EnemyStateCombatDamaged(pEnemy));
		pState->SetStateName("EnemyStateCombatDamaged");
		delete pStatePattern;
		return;
	}

}

EnemyStateCombatIdle::EnemyStateCombatIdle(Enemy* pEnemy)
{
	pEnemy->SetAnimationName("combat_idle");
}
