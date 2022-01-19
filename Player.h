#pragma once
#include "gameObject.h"
#include "playerState.h"


class Player : public GameObject
{
private:


	class PlayerState  m_playerState;
//	class Model* m_Model;
	class Audio* m_shotSE;
	class OBB* m_obb;
	class OBB* m_obbAttack;
	class AnimationModel*  m_Model;

	bool m_isActive = true;
	bool m_movable = true;
	float m_speed;

	XMFLOAT3 m_moveVector;
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

	// 所持品
	// 装備中のアイテム
	// 技
	// 装備中の技
	// 技能

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Move();
	void Jump();
	void Slash();
	void Shoot();
	void Guard();
	void CollisionOther();
	//void VoidDimension();
	void ChangeCameraDir();
	XMFLOAT3 GetMove()const { return m_moveVector; }
	float GetSpeed() { return m_speed; }
	OBB& GetObb() { return *m_obb; }

	bool GetIsActive() const { return m_isActive; }
	bool GetMovable() const { return m_movable; }
	void SetIsActive(bool active) { m_isActive = active; }
	void SetMovable(bool movable) { m_movable = movable; }
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
};

