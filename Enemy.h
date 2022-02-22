#pragma once
#include "gameObject.h"
class EnemyState;

// 敵クラス
class Enemy : public GameObject
{
public:
	// 敵状態データ
	struct EnemyStateData
	{
		float m_EyesightRad;		// 視覚半径
		float m_EyesightAngle;		// 視覚角度
		float m_HearingRad;			// 聴覚半径
		float m_MissedTime;			// プレイヤーを見失う時間
		bool m_IsDiscover;			// プレイヤーを発見状態
		float m_CombatRad;			// 戦闘半径
		EnemyStateData(float eyesight_rad, float eyesight_angle, float hearing_rad, float missed_time, float combat_rad):
			m_EyesightRad(eyesight_rad),
		m_EyesightAngle(eyesight_angle),
		m_HearingRad(hearing_rad),
		m_MissedTime(missed_time),
		m_CombatRad(combat_rad){}
	};
protected:
	class AnimationModel* m_Model;		// モデル
	class Audio* m_explosionSE;			// 爆散SE
	class OBB* m_Obb;					// 当たり判定
	class EnemyState* m_State;			// 状態
	class EnemyBehavior* m_Behavior;	// ビヘイビアツリー管理オブジェクト
	static class EnemyGui* m_EnemyGui;	// GUIオブジェクト
	class HpBar* m_HpBar;				// HPバー
	class Trunk* m_Trunk;				// 体幹
	class TrunkBar* m_TrunkBar;			// 体幹バー
	XMFLOAT3 m_MoveVector;				// 移動方向

	EnemyStateData m_StateData;			// 状態データ
	XMFLOAT3 m_RotationSpeed;			// 回転速度
	float m_MoveSpeed;					// 移動速度
	int m_NowHp;						// 現在HP
	int m_MaxHp;						// 最大HP
	bool m_IsUsingState = true;			// ステートマシーンでAIを操作しているか

	int m_Frame;						// 経過フレーム
	std::string m_AnimationName;		// アニメーション名

private:
	static const std::string VS_FILE_NAME;	// 頂点シェーダー名
	static const std::string PS_FILE_NAME;	// ピクセルシェーダー名
public:
	Enemy();
	virtual void Init();
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 scale);
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 rotation, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	
	// OBBインスタンスゲッター
	OBB& GetObb() { return *m_Obb; }

	// 移動速度ゲッター
	float GetMoveSpeed() { return m_MoveSpeed; }

	// 移動方向セッター
	void SetMoveVector(XMFLOAT3 moveVector) { m_MoveVector = moveVector; }

	// 回転速度セッター
	void SetRotationSpeed(XMFLOAT3 rotationSpeed) { m_RotationSpeed = rotationSpeed; }

	// 状態データゲッター
	EnemyStateData* GetEnemyStateData() { return &m_StateData; }

	// 状態ゲッター
	class EnemyState* GetEnemyState() { return m_State; }
	
	// ビヘイビアツリー名ゲッター
	std::string GetEnemyBehaviorName();

	// ポジションポインターゲッター
	XMFLOAT3* GetpPosition() { return &m_Position; }
	
	// ダメージを与え、HPが0になったらtrueを返す
	bool Damage(int damage);

	// 体幹ゲッター
	Trunk* GetTrunk() { return m_Trunk; }

	// ステートマシーン使用中か
	bool GetIsUsingState() { return m_IsUsingState; }

	// 現在HPゲッター
	int GetNowHp() { return m_NowHp; }

	// 最大HPゲッター
	int GetMaxHp() { return m_MaxHp; }

	// アニメーション名ゲッター
	const std::string& GetAnimationName() const { return m_AnimationName; }

	// アニメーション名セッター
	void SetAnimationName(const std::string& name) {
		m_AnimationName = name;
		ResetAnimationFrame(); }

	// アニメーションフレームリセット
	void ResetAnimationFrame() { m_Frame = 0; }
private:
	// 回転更新
	void UpdateRotation();
	
	// 当たり判定更新
	void UpdateOBB();

	// 移動方向に移動
	void MoveFromMoveVector();

	// 他オブジェクトとの当たり判定
	void CollisionOther();

	// モデル初期化
	void ModelInit();
};

