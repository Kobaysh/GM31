#pragma once
#include "gameObject.h"
class EnemyState;

class Enemy : public GameObject
{
public:
	struct EnemyStateData
	{
		float m_EyesightRad;		// 視覚半径
		float m_EyesightAngle;		// 視覚角度
		float m_HearingRad;		// 聴覚半径
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
//	Model* m_Model;
//	int m_ModelId;
	class AnimationModel* m_Model;
	class Audio* m_explosionSE;
	class OBB* m_Obb;
	class EnemyState* m_State;
	class EnemyBehavior* m_Behavior;
	static class EnemyGui* m_EnemyGui;
	class HpBar* m_HpBar;
	class Trunk* m_Trunk;	// 体幹
	class TrunkBar* m_TrunkBar;
	XMFLOAT3 m_MoveVector;

	EnemyStateData m_StateData;
	XMFLOAT3 m_RotationSpeed;
	float m_MoveSpeed;
	int m_NowHp;
	int m_MaxHp;
	bool m_IsUsingState = true;	// ステートマシーンでAIを操作しているか

	int m_Frame;
	std::string m_AnimationName;

private:
	static const std::string VS_FILE_NAME;
	static const std::string PS_FILE_NAME;
public:
	Enemy();
	virtual void Init();
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 scale);
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 rotation, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	OBB& GetObb() { return *m_Obb; }
	float GetMoveSpeed() { return m_MoveSpeed; }
	void SetMoveVector(XMFLOAT3 moveVector) { m_MoveVector = moveVector; }
	void SetRotationSpeed(XMFLOAT3 rotationSpeed) { m_RotationSpeed = rotationSpeed; }
	EnemyStateData* GetEnemyStateData() { return &m_StateData; }
	class EnemyState* GetEnemyState() { return m_State; }
	std::string GetEnemyBehaviorName();
	XMFLOAT3* GetpPosition() { return &m_Position; }
	
	//	ダメージを与え、HPが0になったらtrueを返す
	bool Damage(int damage);
	Trunk* GetTrunk() { return m_Trunk; }

	bool GetIsUsingState() { return m_IsUsingState; }

	int GetNowHp() { return m_NowHp; }
	int GetMaxHp() { return m_MaxHp; }

	const std::string& GetAnimationName() const { return m_AnimationName; }
	void SetAnimationName(const std::string& name) {
		m_AnimationName = name;
		ResetAnimationFrame(); }
	void ResetAnimationFrame() { m_Frame = 0; }
private:
	void UpdateRotation();
	void UpdateOBB();
	void MoveFromMoveVector();
	void CollisionOther();
	void ModelInit();
};

