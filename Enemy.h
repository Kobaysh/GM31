#pragma once
#include "gameObject.h"
class EnemyState;

class Enemy : public GameObject
{
public:
	struct EnemyStateData
	{
		float m_eyesight_rad;		// 視覚半径
		float m_eyesight_angle;		// 視覚角度
		float m_hearing_rad;		// 聴覚半径
		int m_missed_time;			// プレイヤーを見失う時間
		bool m_isDiscover;			// プレイヤーを発見状態
		float m_combat_rad;			// 戦闘半径
	};
protected:
//	Model* m_model;
	int m_modelId;
	class Audio* m_explosionSE;
	class OBB* m_obb;
	class EnemyState* m_state;
	class EnemyGui* m_enemyGui;
	XMFLOAT3 m_moveVector;

	EnemyStateData m_stateData;
	XMFLOAT3 m_rotationSpeed;
	float m_moveSpeed;
	
public:
	virtual void Init();
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	OBB& GetObb() { return *m_obb; }
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMoveVector(XMFLOAT3 moveVector) { m_moveVector = moveVector; }
	EnemyStateData* GetEnemyStateData() { return &m_stateData; }
	class EnemyState* GetEnemyState() { return m_state; }
private:
	void UpdateRotation();
	void UpdateOBB();
	void MoveFromMoveVector();
	void CollisionOther();
};

