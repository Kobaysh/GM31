#include "enemyStateIdleDiscover.h"
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemyStateCombatIdle.h"
#include "player.h"
#include "enemy.h"

#define NEARLY_ZERO_VALUE 0.001f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.012f)

void EnemyStateIdleDiscover::Update(Enemy * pEnemy)
{
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	XMVECTOR vPlayerPos, vEnemyPos, vToPlayer, vLength;
	float length;
	vPlayerPos = XMLoadFloat3(&player->GetPosition());
	vEnemyPos = XMLoadFloat3(&pEnemy->GetPosition());
	vToPlayer = vPlayerPos - vEnemyPos;
	vLength = XMVector3Length(vToPlayer);
	XMStoreFloat(&length, vLength);

	XMVECTOR vForward = XMLoadFloat3(&pEnemy->GetDirection()->m_forward);
	XMVECTOR vEToPlayer = XMVector3Normalize(vToPlayer);
	XMVECTOR vCross = XMVector3Cross(vForward, vToPlayer);
	int sign;
	sign = vCross.m128_f32[1] < 0.0f ? 1 : -1;

	XMVECTOR vDot = XMVector3Dot(vForward, vEToPlayer);
	//	vDot = XMVector3Normalize(vDot);
	float fDot = 0.0f;
	XMStoreFloat(&fDot, vDot);
	float dir_difference = acosf(fDot);

	if (isfinite(dir_difference) || isnan(dir_difference))
	{
		//	dir_difference = XMConvertToRadians(180.0f);
	}

	float rot = ROTATION_VALUE * sign;
	if (fabsf(dir_difference) <= NEARLY_ZERO_VALUE) {
		dir_difference = 0.0f;
		rot = 0.0f;
	}
	if (fabsf(rot) > fabsf(dir_difference)) {
		rot = dir_difference;
	}

	if (fabsf(pEnemy->GetMoveSpeed()) <= 0.0f) {
		rot = 0.0f;
	}

	XMMATRIX mtxRot;
	mtxRot = XMMatrixRotationY(rot);
	vForward = XMVector3TransformNormal(vForward, mtxRot);
	XMVECTOR vRight = XMLoadFloat3(&pEnemy->GetDirection()->m_right);
	vRight = XMVector3TransformNormal(vRight, mtxRot);
	XMStoreFloat3(&pEnemy->GetDirection()->m_forward, vForward);
	XMStoreFloat3(&pEnemy->GetDirection()->m_right, vRight);

	vDot = XMVector3Dot(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), vForward);
	XMStoreFloat(&fDot, vDot);
	XMFLOAT3 rotation = pEnemy->GetRotation();
	rotation.y = dir_difference;
	pEnemy->SetRotation(rotation);

	// í“¬”¼Œa‚É‹ß‚Ã‚¢‚½‚çí“¬ó‘Ô‚ÉˆÚs
	if (pEnemy->GetEnemyStateData()->m_combat_rad >= length)
	{
		pEnemy->SetMoveVector(XMFLOAT3(0.0f, 0.0f, 0.0f));
		EnemyStatePattern* pStatePattern = 
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateCombatIdle);
		delete pStatePattern;
		return;
	}

	vToPlayer = XMVector3Normalize(vToPlayer);
	XMFLOAT3 moveVector;
	XMStoreFloat3(&moveVector, vToPlayer);
	pEnemy->SetMoveVector(moveVector);
}
