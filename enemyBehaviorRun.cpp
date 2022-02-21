#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemy.h"
#include "player.h"
#include "actionBase.h"
#include "enemyBehavior.h"
#include "enemyBehaviorRun.h"

const float EnemyBehaviorRun::RUN_COMPLETE = 15.0f;

#define NEARLY_ZERO_VALUE 0.001f
#define ROTATION_SPEED (0.01f)
#define ROTATION_VALUE (0.012f)

// �ҋ@
ActionBase::EXE_STATE EnemyBehaviorRun::Run(Enemy * pEnemy,  EnemyBehavior* pBehavior)
{


	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	if (!player)
	{
		pBehavior->ResetTimer();
		return EXE_STATE::FAILED;
	}
	XMVECTOR vPlayerPos, vEnemyPos, vToPlayer, vLength;
	float length;
	vPlayerPos = XMLoadFloat3(&player->GetPosition());
	vEnemyPos = XMLoadFloat3(&pEnemy->GetPosition());
	vToPlayer = vPlayerPos - vEnemyPos;
	//	vToPlayer.m128_f32[1] = 0.0f;
	vLength = XMVector3Length(vToPlayer);
	XMStoreFloat(&length, vLength);

	XMVECTOR vForward = XMLoadFloat3(&pEnemy->GetDirection()->Forward);
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
	vForward = vEToPlayer;
	vForward.m128_f32[1] = 0;
	vForward = XMVector3Normalize(vForward);
	float rot90 = XMConvertToRadians(90.0f);
	XMMATRIX mtxRot;
	mtxRot = XMMatrixRotationY(rot90);
	mtxRot = XMMatrixRotationY(rot);
	//	vForward = XMVector3TransformNormal(vForward, mtxRot);
	XMVECTOR vRight = XMLoadFloat3(&pEnemy->GetDirection()->Right);
	vRight = XMVector3TransformNormal(vForward, mtxRot);
	//	vRight = XMVector3TransformNormal(vRight, mtxRot);
	XMStoreFloat3(&pEnemy->GetDirection()->Forward, vForward);
	XMStoreFloat3(&pEnemy->GetDirection()->Right, vRight);


	vDot = XMVector3Dot(XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f), vForward);
	if (vForward.m128_f32[0] > 0.0f)
	{
		vDot = XMVector3Dot(vForward, XMVectorSet(0.0f, 0.0f, -1.0f, 0.0f));
	}
	XMStoreFloat(&fDot, vDot);

	XMFLOAT3 rotation = pEnemy->GetRotation();
	rotation.y = acosf(fDot);
	pEnemy->SetRotation(rotation);

	// �퓬���a�ɋ߂Â����琳��I��
	if (pEnemy->GetEnemyStateData()->m_combat_rad >= length)
	{
		pEnemy->SetMoveVector(XMFLOAT3(0.0f, 0.0f, 0.0f));
		pBehavior->ResetTimer();
		return EXE_STATE::COMPLETE;
	}

	vToPlayer = XMVector3Normalize(vToPlayer);
	XMFLOAT3 moveVector;
	XMStoreFloat3(&moveVector, vToPlayer);
	pEnemy->SetMoveVector(moveVector);

	if (pBehavior->GetTimer() >= RUN_COMPLETE)
	{
		pBehavior->ResetTimer();
		return EXE_STATE::FAILED;
	}

	return EXE_STATE::RUNNING;
}