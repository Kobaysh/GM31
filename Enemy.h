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

	float m_eyesight_rad;		// ���o���a
	float m_eyesight_angle;		// ���o�p�x
	float m_hearing_rad;		// ���o���a
	int m_missed_time;			// �v���C���[������������
	bool m_isDiscover;			// �v���C���[�𔭌����

	float m_moveSpeed;

public:
	virtual void Init();
	void Uninit();
	void Update();
	void Draw();
	OBB& GetObb() { return *m_obb; }
	float GetMoveSpeed() { return m_moveSpeed; }
};

