#include "main.h"
#include "manager.h"
#include "scene.h"
#include "enemyStateIdleIdle.h"
#include "enemyStateIdleBeware.h"
#include "enemyStateIdleDiscover.h"
#include "player.h"
#include "enemy.h"


void EnemyStateIdleBeware::Update(Enemy * pEnemy)
{
		Enemy::EnemyStateData* stateData =  pEnemy->GetEnemyStateData();
	//	if (m_radiusDiscoverPlayer <= 0.0f)
		if (stateData->m_eyesight_rad <= 0.0f)
		{
			EnemyStatePattern* pStatePattern =
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateIdleIdle);
			delete pStatePattern;
			return;
		}
		Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	
		XMVECTOR vPlayerPos, vEnemyPos, vLength;
		vPlayerPos = XMLoadFloat3(&player->GetPosition());
		vEnemyPos = XMLoadFloat3(&pEnemy->GetPosition());
		vLength = XMVector3Length(vEnemyPos - vPlayerPos);
		float lengthEToP;
		XMStoreFloat(&lengthEToP, vLength);
		lengthEToP = fabsf(lengthEToP);
		if (lengthEToP <= stateData->m_eyesight_rad)
		{
			// ƒvƒŒƒCƒ„[”­Œ©
			pEnemy->GetEnemyStateData()->m_isDiscover = true;
			EnemyStatePattern* pStatePattern =
			pEnemy->GetEnemyState()->ChangeState(new EnemyStateIdleDiscover);
			delete pStatePattern;
			return;
		}
}
