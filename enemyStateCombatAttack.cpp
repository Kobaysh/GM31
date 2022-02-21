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

Audio* EnemyStateCombatAttack::m_attackSE = nullptr;
Audio* EnemyStateCombatAttack::m_guardSE = nullptr;
Audio* EnemyStateCombatAttack::m_repelSE = nullptr;

void EnemyStateCombatAttack::Init()
{
	if (!m_attackSE)
	{
		m_attackSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
		m_attackSE->Load("asset\\audio\\se\\punch.wav");
	}
	if (!m_guardSE)
	{
		m_guardSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
		m_guardSE->Load("asset\\audio\\se\\guard.wav");
	}
	if (!m_repelSE)
	{
		m_repelSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
		m_repelSE->Load("asset\\audio\\se\\repel.wav");
	}
}

void EnemyStateCombatAttack::Update(Enemy * pEnemy)
{
	m_timer += 0.1f;
	Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);

	if (!m_isAttacking && m_timer >= 6.0f)
	{
		if (pEnemy->GetAnimationName() != "kick")
		{
			pEnemy->SetAnimationName("kick");
			pEnemy->ResetAnimationFrame();
		}
	}


	if (!m_isAttacking && m_timer >= 10.0f)
	{
		m_isAttacking = true;
		XMFLOAT3 obbPos;
		XMVECTOR vObbPos = XMLoadFloat3(&pEnemy->GetPosition()) + XMLoadFloat3(&pEnemy->GetDirection()->Forward) * 2;
		XMStoreFloat3(&obbPos, vObbPos);
		//obbPos.y += 1.0f;
		m_obbAttack = nullptr;
		m_obbAttack = new OBB(obbPos, pEnemy->GetRotation(), XMFLOAT3(1.0f, 2.0f,1.0f));
		ManagerT::GetScene()->AddGameObject(m_obbAttack, GameObject::GOT_OBJECT3D);
		m_timer = 0.0f;
	}
	if (!pPlayer) return;

	if (m_isAttacking)
	{
		if (OBB::ColOBBs(*m_obbAttack, pPlayer->GetObb()))
		{
			// �U����������
			m_isAttacking = false;
			m_obbAttack->SetDead();
			m_obbAttack = nullptr;
			
			if(pPlayer->GetIsGuarding())
			{
				// �v���C���[���K�[�h���Ȃ�
				
				// �v���C���[�̃K�[�h���w��t���[���ȉ��Ȃ�e�����
				if (pPlayer->GetTimerGuard() <= 1.5f)
				{
					m_repelSE->Play();
					pEnemy->GetTrunk()->ChangeNowTrunk(10);
				}
				else
				{
					m_guardSE->Play();
					pPlayer->GetTrunk()->ChangeNowTrunk(10);
				}
			}
			else
			{
				m_attackSE->Play();
				pPlayer->GetTrunk()->ChangeNowTrunk(10);
				pPlayer->Damage(1);
			}
			
			EnemyStatePattern* pStatePattern = 
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle(pEnemy));
			pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatIdle");
			delete pStatePattern;
			return;
		}
		// �U���A�j���[�V�������I�������false
		if (m_timer >= 12.0f)
		{
			m_isAttacking = false;
			m_obbAttack->SetDead();
			m_obbAttack = nullptr;
			EnemyStatePattern* pStatePattern = 
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle(pEnemy));
			pEnemy->GetEnemyState()->SetStateName("EnemyStateCombatIdle");
			delete pStatePattern;
			return;
		}
		//if(�A�j���[�V�����I���H)
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
		/*delete m_obbAttack;
		m_obbAttack = nullptr;*/
		m_obbAttack->SetDead();
	}
}
