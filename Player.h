#pragma once
#include "gameObject.h"


class Player : public GameObject
{
private:


	class HpPlayer* m_HpBar = nullptr;
//	class Model* m_Model;
	class Audio* m_SlashSE= nullptr;
	class OBB* m_Obb= nullptr;
	class OBB* m_ObbAttack= nullptr;
	class AnimationModel*  m_Model= nullptr;
	class LockOnCircle* m_LockOnCircle = nullptr;

	bool m_IsActive = true;
	bool m_IsMovable = true;
	float m_Speed;

	XMFLOAT3 m_MoveVector;
	int m_Sign;

	bool m_IsAttack = false;
	bool m_IsGuard = false;
	bool m_Isjump = false;
	float m_JumpForce;

	float m_TimerAttack;
	float m_TimerGuard;

	int m_NowHp;					// ヒットポイント
	int m_MaxHp;					// Maxヒットポイント
	int m_AttackPower;				// 攻め力

	int m_SoundVolume;				// プレイヤーの出す音
	
 	class Trunk* m_Trunk;

	int m_Frame;
	std::string m_AnimationName;

	float m_LockOnRad;				// ロックオン距離

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	void ChangeCameraDir();
	XMFLOAT3 GetMove()const { return m_MoveVector; }
	float GetSpeed() { return m_Speed; }
	OBB& GetObb() { return *m_Obb; }

	bool GetIsActive() const { return m_IsActive; }
	bool GetMovable() const { return m_IsMovable; }
	void SetIsActive(bool active) { m_IsActive = active; }
	void SetMovable(bool movable) { m_IsMovable = movable; }
	bool GetIsGuarding() { return m_IsGuard; }
	float GetTimerGuard() { return m_TimerGuard; }
	Trunk* GetTrunk() { return m_Trunk; }

	bool Damage(int damage);
	int GetNowHp() { return m_NowHp; }
	int GetMaxHp() { return m_MaxHp; }
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

