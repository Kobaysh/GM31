#pragma once
#include "gameObject.h"
#include "playerState.h"


class Player : public GameObject
{
private:


	class PlayerState  m_playerState;
	class HpPlayer* m_hpBar = nullptr;
//	class Model* m_model;
	class Audio* m_slashSE= nullptr;
	class OBB* m_Obb= nullptr;
	class OBB* m_obbAttack= nullptr;
	class AnimationModel*  m_model= nullptr;
	class LockOnCircle* m_lockOnCircle = nullptr;

	bool m_IsActive = true;
	bool m_IsMovable = true;
	float m_speed;

	XMFLOAT3 m_MoveVector;
	int m_sign;

	bool m_isAttack = false;
	bool m_isGuard = false;
	bool m_isjump = false;
	float m_jumpForce;

	float m_timerAttack;
	float m_timerGuard;

	int m_nowHp;					// ヒットポイント
	int m_maxHp;					// Maxヒットポイント
	int m_attackPower;				// 攻め力

	int m_soundVolume;				// プレイヤーの出す音
	int m_nowWepon;					// 現在装備中の忍び義手の種類(番号)
	
 	class Trunk* m_trunk;

	int m_frame;
	std::string m_animationName;

	float m_lockOnRad;				// ロックオン距離

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	//void VoidDimension();
	void ChangeCameraDir();
	XMFLOAT3 GetMove()const { return m_MoveVector; }
	float GetSpeed() { return m_speed; }
	OBB& GetObb() { return *m_Obb; }

	bool GetIsActive() const { return m_IsActive; }
	bool GetMovable() const { return m_IsMovable; }
	void SetIsActive(bool active) { m_IsActive = active; }
	void SetMovable(bool movable) { m_IsMovable = movable; }
	bool GetIsGuarding() { return m_isGuard; }
	float GetTimerGuard() { return m_timerGuard; }
	Trunk* GetTrunk() { return m_trunk; }

	bool Damage(int damage);
	int GetNowHp() { return m_nowHp; }
	int GetMaxHp() { return m_maxHp; }
private:
	void ModelInit();
	void UpdateObb();
	void MoveFromMoveVector();
	void ChangeAnimation(const char* animationName);
	void Move();
	void Jump();
	void Slash();
	void Shoot();
	void Guard();
	void LockOn();
	void MouseActive();
	void CollisionOther();
};

