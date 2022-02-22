#include "enemyState.h"
//#include "main.h"
//#include "manager.h"
//#include "renderer.h"
//#include "scene.h"
//#include "gameObject.h"
//#include "player.h"
#include "enemy.h"
#include "enemyStateIdleIdle.h"

/*
const char* EnemyState::enumChar_Enemy_State[EnemyState::MAX] = 
{
	"IDLE_IDLE",
	"IDLE_WALK",				// ŽUô
	"IDLE_NINJAEXECUTION",	// ”EŽE
	"IDLE_SURPRISE",			// ‹Á‚­
	"IDLE_BEWARE",			// Œx‰ú‚·‚é
	"IDLE_DISCOVER",			// ”­Œ©‚·‚é
	"IDLE_MOVE_TO_PLAYER",	// ƒvƒŒƒCƒ„[‚Ì‚à‚Æ‚ÉˆÚ“®
	// í“¬
	"COMBAT_IDLE",			// ‘Ò‹@
	"COMBAT_ATTACK",			// UŒ‚
	"COMBAT_GUARD",			// ƒK[ƒh
	"COMBAT_DAMAGED",			// ƒ_ƒ[ƒW‚ðŽó‚¯‚é
	"COMBAT_NINJAEXECUTION",	// ”EŽE
	"COMBAT_DEAD",			// Ž€–S
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

//void EnemyState::Init(void * stateData)
////void EnemyState::Init(Enemy::EnemyStateData * stateData)
//{
//	m_pStateData = stateData;
//}

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
	m_Timer += 0.1f;
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
	Enemy::EnemyStateData* stateData =  m_enemy->GetEnemyStateData();
//	if (m_radiusDiscoverPlayer <= 0.0f)
	if (stateData->m_eyesight_rad <= 0.0f)
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
	if (lengthEToP <= stateData->m_eyesight_rad)
	{
		// ƒvƒŒƒCƒ„[”­Œ©
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
	
	XMVECTOR vForward = XMLoadFloat3(&m_enemy->GetDirection()->Forward);
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
	
	if (fabsf(m_enemy->GetMoveSpeed()) <= 0.0f) {
		rot = 0.0f;
	}

	XMMATRIX mtxRot;
	mtxRot = XMMatrixRotationY(rot);
	vForward = XMVector3TransformNormal(vForward, mtxRot);
	XMVECTOR vRight = XMLoadFloat3(&m_enemy->GetDirection()->Right);
	vRight = XMVector3TransformNormal(vRight, mtxRot);
	XMStoreFloat3(&m_enemy->GetDirection()->Forward, vForward);
	XMStoreFloat3(&m_enemy->GetDirection()->Right, vRight);

	vDot = XMVector3Dot(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f), vForward);
	XMStoreFloat(&fDot, vDot);
	XMFLOAT3 rotation = m_enemy->GetRotation();
	rotation.y = dir_difference;
	m_enemy->SetRotation(rotation);

	// í“¬”¼Œa‚É‹ß‚Ã‚¢‚½‚çí“¬ó‘Ô‚ÉˆÚs
//	if (m_enemy->GetEnemyStateData().m_combat_rad >= length)
	if (m_enemy->GetEnemyStateData()->m_combat_rad >= length)
	{
		m_enemy->SetMoveVector(XMFLOAT3(0.0f, 0.0f, 0.0f));
		ChangeState(COMBAT_IDLE);
		return;
	}

	vToPlayer = XMVector3Normalize(vToPlayer);
	XMFLOAT3 moveVector;
	XMStoreFloat3(&moveVector, vToPlayer);
	m_enemy->SetMoveVector(moveVector);
	//vEnemyPos += vToPlayer * m_enemy->GetMoveSpeed();
	//XMFLOAT3 enemyPos;
	//XMStoreFloat3(&enemyPos, vEnemyPos);
	//m_enemy->SetPosition(enemyPos);
}

void EnemyState::Combat_Idle()
{
	// ƒvƒŒƒCƒ„[‚Ì•ûŒü‚ðŒü‚«‚È‚ª‚çŠÔ‡‚¢‚ðˆê’è‚É­‚µ‰ñ“]

	// Šm—¦‚ÅUŒ‚
	
	// ƒvƒŒƒCƒ„[‚ÌUŒ‚‚É‰ž‚¶‚ÄŠm—¦‚Å–hŒä
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
	// ”EŽE‚³‚ê‚éƒAƒjƒ[ƒVƒ‡ƒ“

	// Ž€–Só‘Ô‚ÉˆÚs
}

void EnemyState::Combat_Dead()
{
}

*/

EnemyState::EnemyState():m_pStatePattern(new EnemyStateIdleIdle)
{
	
}

EnemyState::~EnemyState()
{
	if (m_pStatePattern)
	{
		delete m_pStatePattern;
		m_pStatePattern = nullptr;
	}
}

void EnemyState::Update(Enemy * pEnemy)
{
	m_pStatePattern->Update(pEnemy);
}

EnemyStatePattern * EnemyState::ChangeState(EnemyStatePattern * pStatePattern)
{
	EnemyStatePattern* temp = m_pStatePattern;
	m_pStatePattern = pStatePattern;
	return temp;
}
