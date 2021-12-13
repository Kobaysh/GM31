#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "obb.h"
#include "enemyStateCombatAttack.h"
#include "enemyStateCombatIdle.h"


void EnemyStateCombatAttack::Update(Enemy * pEnemy)
{
	m_timer += 0.1f;
	Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);

	if (!m_isAttacking && m_timer >= 10.0f)
	{
		m_isAttacking = true;
		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&pEnemy->GetPosition()) + XMLoadFloat3(&pEnemy->GetDirection()->m_forward);
		XMStoreFloat3(&obbPos, vObbPos);
		m_obbAttack = new OBB(obbPos, pEnemy->GetRotation(), XMFLOAT3(1.0f, 1.0f, 1.0f));

	}

	if (m_isAttacking)
	{
		if (OBB::ColOBBs(*m_obbAttack, pPlayer->GetObb()))
		{
			// 攻撃当たった
			m_isAttacking = false;
			delete m_obbAttack;
			m_obbAttack = nullptr;
			/*
			if(ガードされた？)
			{

			}
			else
			{

			}
			*/
			return;
		}
		// 攻撃アニメーションが終わったらfalse
		//if(アニメーション終了？)
		//{
		// m_isAttacking = false;
		//delete m_obbAttack;
		//m_obbAttack = nullptr;
		//return;
		//}
	}
}

EnemyStateCombatAttack::~EnemyStateCombatAttack()
{
	if (m_obbAttack)
	{
		delete m_obbAttack;
		m_obbAttack = nullptr;
	}
}
