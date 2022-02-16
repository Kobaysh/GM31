#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"
#include "actionBase.h"
#include "enemyBehaviorLookingFor.h"

const float EnemyBehaviorLookingFor::LOOKINGFOR_COMPLETE = 5.0f;


// �ҋ@
ActionBase::EXE_STATE EnemyBehaviorLookingFor::Run(Enemy * pEnemy)
{

	m_timer += UPDATE_TIMER_AMOUNT;

	Enemy::EnemyStateData* stateData =  pEnemy->GetEnemyStateData();
	if (stateData->m_eyesight_rad <= 0.0f)
	{
		// ���E��0�ȉ��Ȃ玸�s
		m_timer = 0.0f;
		return EXE_STATE::FAILED;
	}

	// �v���C���[�Ƃ̋����𑪂�
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player) return  EXE_STATE::FAILED;
	XMVECTOR vPlayerPos, vEnemyPos, vLength;
	vPlayerPos = XMLoadFloat3(&player->GetPosition());
	vEnemyPos = XMLoadFloat3(&pEnemy->GetPosition());
	vLength = XMVector3Length(vEnemyPos - vPlayerPos);
	float lengthEToP;
	XMStoreFloat(&lengthEToP, vLength);
	lengthEToP = fabsf(lengthEToP);
	if (lengthEToP <= stateData->m_eyesight_rad)
	{
		// �v���C���[����
		pEnemy->GetEnemyStateData()->m_isDiscover = true;
		pEnemy->SetRotationSpeed(XMFLOAT3(0.0f,0.0f,0.0f));
		m_timer = 0.0f;
		return EXE_STATE::COMPLETE;
	}
	XMFLOAT3 rot = pEnemy->GetRotation();
	XMFLOAT3 rotSpeed = XMFLOAT3(0.0f, 0.01f, 0.0f);
	//rot.y += rotSpeed.y;
	//pEnemy->SetRotation(rot);
	//pEnemy->SetRotationSpeed(rotSpeed);

	if (m_timer >= LOOKINGFOR_COMPLETE)
	{
		m_timer = 0.0f;
		return EXE_STATE::FAILED;
	}

	return EXE_STATE::RUNNING;
}
