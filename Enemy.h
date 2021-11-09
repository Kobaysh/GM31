#pragma once
#include "gameObject.h"
#include "enemyState.h"
class Enemy : public GameObject
{
protected:
//	Model* m_model;
	int m_modelId;
	class Audio* m_explosionSE;
	class OBB* m_obb;
	class EnemyState* m_state;

	float m_eyesight_rad;		// 視覚半径
	float m_eyesight_angle;		// 視覚角度
	float m_hearing_rad;		// 聴覚半径
	int m_missed_time;			// プレイヤーを見失う時間
	bool m_isDiscover;			// プレイヤーを発見状態

	float m_moveSpeed;

public:
	virtual void Init();
	void Uninit();
	void Update();
	void Draw();
	OBB& GetObb() { return *m_obb; }
	float GetMoveSpeed() { return m_moveSpeed; }
};

