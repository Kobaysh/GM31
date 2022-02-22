#pragma once
#include "gameObject.h"

// プレイヤークラス
class Player : public GameObject
{
private:
	class HpPlayer* m_HpBar = nullptr;				// HPバー
//	class Model* m_Model;
	class Audio* m_SlashSE= nullptr;				// 攻撃SE
	class OBB* m_Obb= nullptr;						// 当たり判定
	class OBB* m_ObbAttack= nullptr;				// 攻撃判定
	class AnimationModel*  m_Model= nullptr;		// モデル
	class LockOnCircle* m_LockOnCircle = nullptr;	// ロックオン中の円
	class Trunk* m_Trunk;							// 体幹

	bool m_IsActive = true;							// 行動可能か
	bool m_IsMovable = true;						// 移動可能か
	bool m_IsAttack = false;						// 攻撃中か
	bool m_IsGuard = false;							// ガード中か
	bool m_Isjump = false;							// ジャンプ中か
	float m_JumpForce;								// ジャンプ力
	float m_TimerAttack;							// 攻撃中タイマー
	float m_TimerGuard;								// ガード中タイマー
	float m_LockOnRad;								// ロックオン距離
	float m_Speed;									// 速度
	XMFLOAT3 m_MoveVector;							// 移動方向
	int m_Sign;										// 符号
	int m_NowHp;									// 現在HP
	int m_MaxHp;									// 最大HP
	int m_AttackPower;								// 攻め力
	int m_SoundVolume;								// プレイヤーの出す音
	int m_Frame;									// 経過フレーム
	std::string m_AnimationName;					// アニメーション名
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// カメラ方向変更
	void ChangeCameraDir();

	// 移動方向ゲッター
	XMFLOAT3 GetMove()const { return m_MoveVector; }
	
	// 移動速度ゲッター
	float GetSpeed() { return m_Speed; }
	
	// 当たり判定ゲッター
	OBB& GetObb() { return *m_Obb; }

	// 行動可能か
	bool GetIsActive() const { return m_IsActive; }
	
	// 移動可能か
	bool GetMovable() const { return m_IsMovable; }
	
	// 行動可能セッター
	void SetIsActive(bool active) { m_IsActive = active; }
	
	// 移動可能セッター
	void SetMovable(bool movable) { m_IsMovable = movable; }
	
	// ガード中か
	bool GetIsGuarding() { return m_IsGuard; }
	
	// ガード中タイマーゲッター
	float GetTimerGuard() { return m_TimerGuard; }
	
	// 体幹ゲッター
	Trunk* GetTrunk() { return m_Trunk; }
	
	// ダメージを与える
	bool Damage(int damage);
	
	// 現在HPゲッター
	int GetNowHp() { return m_NowHp; }
	
	// 最大HPゲッター
	int GetMaxHp() { return m_MaxHp; }
private:
	
	// モデル初期化
	void ModelInit();
	
	// 当たり判定更新
	void UpdateObb();
	
	// 移動方向へ移動
	void MoveFromMoveVector();
	
	// アニメーション変更
	void ChangeAnimation(const char* animationName);
	
	// 移動
	void Move();
	
	// ジャンプ
	void Jump();
	
	// 攻撃
	void Slash();
	
	// 撃つ
	void Shoot();
	
	// ガード
	void Guard();
	
	// ロックオン
	void LockOn();
	
	// マウスとキーボード切替
	void MouseActive();
	
	// 他オブジェクトとの当たり判定
	void CollisionOther();
};

