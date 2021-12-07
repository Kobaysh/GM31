#include "enemyState.h"
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "gameObject.h"
#include "player.h"
#include "enemy.h"

const char* EnemyState::enumChar_Enemy_State[EnemyState::MAX] = 
{
	"IDLE_IDLE",
	"IDLE_WALK",				// 散策
	"IDLE_NINJAEXECUTION",	// 忍殺
	"IDLE_SURPRISE",			// 驚く
	"IDLE_BEWARE",			// 警戒する
	"IDLE_DISCOVER",			// 発見する
	"IDLE_MOVE_TO_PLAYER",	// プレイヤーのもとに移動
	// 戦闘
	"COMBAT_IDLE",			// 待機
	"COMBAT_ATTACK",			// 攻撃
	"COMBAT_GUARD",			// ガード
	"COMBAT_DAMAGED",			// ダメージを受ける
	"COMBAT_NINJAEXECUTION",	// 忍殺
	"COMBAT_DEAD",			// 死亡
};

//void EnemyState::Init(float radDiscPlayer)
//{
//	m_radiusDiscoverPlayer = radDiscPlayer;
//}
//
//void EnemyState::Init(Enemy::EnemyStateData stateData)
//{
//	m_radiusDiscoverPlayer = stateData.m_eyesight_rad;
//}

void EnemyState::Init(Enemy::EnemyStateData * stateData)
{
	m_pStateData = stateData;
}

void EnemyState::Update()
{
	UpdateAI();
}

void EnemyState::ChangeState(En_Enemy_State newState)
{
    m_nextState = newState;
}

void EnemyState::SetAI()
{
	AIMainRoutine();
	if (m_isAiStaterunning) return;
	if (m_nowState != m_nextState) {
		m_nowState = m_nextState;
	}
}

void EnemyState::AIMainRoutine()
{

}

void EnemyState::UpdateAI()
{
	SetAI();
	m_timer += 0.1f;
	switch (m_nowState)
	{
	case EnemyState::NONE:
		break;
	case EnemyState::IDLE_IDLE:
		Idle_Idle();
		break;
	case EnemyState::IDLE_WALK:
		Idle_Walk();
		break;
	case EnemyState::IDLE_NINJAEXECUTION:
		break;
	case EnemyState::IDLE_SURPRISE:
		break;
	case EnemyState::IDLE_BEWARE:
		Idle_Beware();
		break;
	case EnemyState::IDLE_DISCOVER:
		Idle_Discover();
		break;
	case EnemyState::IDLE_MOVE_TO_PLAYER:
		Idle_MoveToPlayer();
		break;
	case EnemyState::COMBAT_IDLE:
		break;
	case EnemyState::COMBAT_ATTACK:
		break;
	case EnemyState::COMBAT_GUARD:
		break;
	case EnemyState::COMBAT_DAMAGED:
		break;
	case EnemyState::COMBAT_NINJAEXECUTION:
		break;
	case EnemyState::COMBAT_DEAD:
		break;
	case EnemyState::MAX:
		break;
	default:
		break;
	}
}

void EnemyState::Idle_Idle()
{
	ChangeState(IDLE_BEWARE);
}

void EnemyState::Idle_Walk()
{
}

void EnemyState::Idle_NinjaExcution()
{
}

void EnemyState::Idle_Surprize()
{
}

void EnemyState::Idle_Beware()
{
//	if (m_radiusDiscoverPlayer <= 0.0f)
	if (m_pStateData->m_eyesight_rad <= 0.0f)
	{
		ChangeState(IDLE_IDLE);
		return;
	}
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);

	XMVECTOR vPlayerPos, vEnemyPos, vLength;
	vPlayerPos = XMLoadFloat3(&player->GetPosition());
	vEnemyPos = XMLoadFloat3(&m_enemy->GetPosition());
	vLength = XMVector3Length(vEnemyPos - vPlayerPos);
	float lengthEToP;
	XMStoreFloat(&lengthEToP, vLength);
	lengthEToP = fabsf(lengthEToP);
	if (lengthEToP <= m_pStateData->m_eyesight_rad)
	{
		// プレイヤー発見
		ChangeState(IDLE_DISCOVER);
	}

}

void EnemyState::Idle_Discover()
{
	ChangeState(IDLE_MOVE_TO_PLAYER);
}

void EnemyState::Idle_MoveToPlayer()
{
	Player* player = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GOT_OBJECT3D);
	XMVECTOR vPlayerPos, vEnemyPos, vToPlayer, vLength;
	float length;
	vPlayerPos = XMLoadFloat3(&player->GetPosition());
	vEnemyPos = XMLoadFloat3(&m_enemy->GetPosition());
	vToPlayer = vPlayerPos - vEnemyPos;
	vLength = XMVector3Length(vToPlayer);
	XMStoreFloat(&length, vLength);
	

	// 戦闘半径に近づいたら戦闘状態に移行
//	if (m_enemy->GetEnemyStateData().m_combat_rad >= length)
	if (m_pStateData->m_combat_rad >= length)
	{
		ChangeState(COMBAT_IDLE);
	}

	vToPlayer = XMVector3Normalize(vToPlayer);
	vEnemyPos += vToPlayer * m_enemy->GetMoveSpeed();
	XMFLOAT3 enemyPos;
	XMStoreFloat3(&enemyPos, vEnemyPos);
	m_enemy->SetPosition(enemyPos);
}

void EnemyState::Combat_Idle()
{

}

void EnemyState::Combat_Attack()
{
}

void EnemyState::Combat_Guard()
{
}

void EnemyState::Combat_Damaged()
{
}

void EnemyState::Combat_Ninjaexecution()
{
}

void EnemyState::Combat_Dead()
{
}
