#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"
#include "actionBase.h"
#include "enemyBehavior.h"
#include "enemyBehaviorLookingFor.h"

const float EnemyBehaviorLookingFor::LOOKINGFOR_COMPLETE = 5.0f;


// 待機
ActionBase::EXE_STATE EnemyBehaviorLookingFor::Run(Enemy * pEnemy, EnemyBehavior* pBehavior)
{



	Enemy::EnemyStateData* stateData =  pEnemy->GetEnemyStateData();
	if (stateData->m_EyesightRad <= 0.0f)
	{
		// 視界が0以下なら失敗
		pBehavior->ResetTimer();
		return EXE_STATE::FAILED;
	}

	// プレイヤーとの距離を測る
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player) return  EXE_STATE::FAILED;
	XMVECTOR vPlayerPos, vEnemyPos, vLength;
	vPlayerPos = XMLoadFloat3(&player->GetPosition());
	vEnemyPos = XMLoadFloat3(&pEnemy->GetPosition());
	vLength = XMVector3Length(vEnemyPos - vPlayerPos);
	float lengthEToP;
	XMStoreFloat(&lengthEToP, vLength);
	lengthEToP = fabsf(lengthEToP);
	if (lengthEToP <= stateData->m_EyesightRad)
	{
		// プレイヤー発見
		pEnemy->GetEnemyStateData()->m_IsDiscover = true;
		pEnemy->SetRotationSpeed(XMFLOAT3(0.0f,0.0f,0.0f));
		pBehavior->ResetTimer();
		return EXE_STATE::COMPLETE;
	}
	XMFLOAT3 rot = pEnemy->GetRotation();
	XMFLOAT3 rotSpeed = XMFLOAT3(0.0f, 0.01f, 0.0f);
	//rot.y += rotSpeed.y;
	//pEnemy->SetRotation(rot);
	//pEnemy->SetRotationSpeed(rotSpeed);

	if (pBehavior->GetTimer() >= LOOKINGFOR_COMPLETE)
	{
		pBehavior->ResetTimer();
		return EXE_STATE::FAILED;
	}

	return EXE_STATE::RUNNING;
}
