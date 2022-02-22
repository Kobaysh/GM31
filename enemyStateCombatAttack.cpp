#include "main.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "enemy.h"
#include "obb.h"
#include "audio.h"
#include "enemyStateCombatAttack.h"
#include "enemyStateCombatIdle.h"
#include "trunk.h"

Audio* EnemyStateCombatAttack::m_AttackSE = nullptr;
Audio* EnemyStateCombatAttack::m_GuardSE = nullptr;
Audio* EnemyStateCombatAttack::m_RepelSE = nullptr;

void EnemyStateCombatAttack::Init()
{
	if (!m_AttackSE)
	{
		m_AttackSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
		m_AttackSE->Load("asset\\audio\\se\\punch.wav");
	}
	if (!m_GuardSE)
	{
		m_GuardSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
		m_GuardSE->Load("asset\\audio\\se\\guard.wav");
	}
	if (!m_RepelSE)
	{
		m_RepelSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
		m_RepelSE->Load("asset\\audio\\se\\repel.wav");
	}
}

void EnemyStateCombatAttack::Update(Enemy * pEnemy)
{
	m_Timer += 0.1f;
	Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);

	if (!m_IsAttacking && m_Timer >= 6.0f)
	{
		if (pEnemy->GetAnimationName() != "kick")
		{
			pEnemy->SetAnimationName("kick");
			pEnemy->ResetAnimationFrame();
		}
	}


	if (!m_IsAttacking && m_Timer >= 10.0f)
	{
		m_IsAttacking = true;
		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&pEnemy->GetPosition()) + XMLoadFloat3(&pEnemy->GetDirection()->Forward) * 2;
		XMStoreFloat3(&obbPos, vObbPos);
		//obbPos.y += 1.0f;
		m_ObbAttack = nullptr;
		m_ObbAttack = new OBB(obbPos, pEnemy->GetRotation(), XMFLOAT3(1.0f, 2.0f,1.0f));
		ManagerT::GetScene()->AddGameObject(m_ObbAttack, GameObject::GOT_OBJECT3D);
		m_Timer = 0.0f;
	}
	if (!pPlayer) return;

	if (m_IsAttacking)
	{
		if (OBB::ColOBBs(*m_ObbAttack, pPlayer->GetObb()))
		{
			// 攻撃当たった
			m_IsAttacking = false;
			m_ObbAttack->SetDead();
			m_ObbAttack = nullptr;
			
			if(pPlayer->GetIsGuarding())
			{
				// プレイヤーがガード中なら
				
				// プレイヤーのガードが指定フレーム以下なら弾かれる
				if (pPlayer->GetTimerGuard() <= 1.5f)
				{
					m_RepelSE->Play();
					pEnemy->GetTrunk()->ChangeNowTrunk(10);
				}
				else
				{
					m_GuardSE->Play();
					pPlayer->GetTrunk()->ChangeNowTrunk(10);
				}
			}
			else
			{
				m_AttackSE->Play();
				pPlayer->GetTrunk()->ChangeNowTrunk(10);
				pPlayer->Damage(1);
			}
			
			EnemyStatePattern* pStatePattern = 
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle(pEnemy));
			pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatIdle");
			delete pStatePattern;
			return;
		}
		// 攻撃アニメーションが終わったらfalse
		if (m_Timer >= 12.0f)
		{
			m_IsAttacking = false;
			m_ObbAttack->SetDead();
			m_ObbAttack = nullptr;
			EnemyStatePattern* pStatePattern = 
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle(pEnemy));
			pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatIdle");
			delete pStatePattern;
			return;
		}
		//if(アニメーション終了？)
		//{
		// m_IsAttacking = false;
		//delete m_ObbAttack;
		//m_ObbAttack = nullptr;
		//return;
		//}
	}
}

EnemyStateCombatAttack::~EnemyStateCombatAttack()
{
	if (m_ObbAttack)
	{
		/*delete m_ObbAttack;
		m_ObbAttack = nullptr;*/
		m_ObbAttack->SetDead();
	}
}
