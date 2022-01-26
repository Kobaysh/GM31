#pragma once
#include "gameObject.h"
class EnemyState;

class Enemy : public GameObject
{
public:
	struct EnemyStateData
	{
		float m_eyesight_rad;		// ���o���a
		float m_eyesight_angle;		// ���o�p�x
		float m_hearing_rad;		// ���o���a
		float m_missed_time;			// �v���C���[������������
		bool m_isDiscover;			// �v���C���[�𔭌����
		float m_combat_rad;			// �퓬���a
		EnemyStateData(float eyesight_rad, float eyesight_angle, float hearing_rad, float missed_time, float combat_rad):
			m_eyesight_rad(eyesight_rad),
		m_eyesight_angle(eyesight_angle),
		m_hearing_rad(hearing_rad),
		m_missed_time(missed_time),
		m_combat_rad(combat_rad){}
	};
protected:
//	Model* m_model;
//	int m_modelId;
	class AnimationModel* m_model;
	class Audio* m_explosionSE;
	class OBB* m_obb;
	class EnemyState* m_state;
	static class EnemyGui* m_enemyGui;
	class HpBar* m_hpBar;
	class Trunk* m_trunk;	// �̊�
	XMFLOAT3 m_moveVector;

	EnemyStateData m_stateData;
	XMFLOAT3 m_rotationSpeed;
	float m_moveSpeed;
	int m_hp;
	int m_maxHp;
	bool m_isUsingState;	// �X�e�[�g�}�V�[����AI�𑀍삵�Ă��邩

	int m_frame;
	std::string m_animationName;
public:
	Enemy();
	virtual void Init();
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 scale);
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 rotation, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	OBB& GetObb() { return *m_obb; }
	float GetMoveSpeed() { return m_moveSpeed; }
	void SetMoveVector(XMFLOAT3 moveVector) { m_moveVector = moveVector; }
	void SetRotationSpeed(XMFLOAT3 rotationSpeed) { m_rotationSpeed = rotationSpeed; }
	EnemyStateData* GetEnemyStateData() { return &m_stateData; }
	class EnemyState* GetEnemyState() { return m_state; }
	
	//	�_���[�W��^���AHP��0�ɂȂ�����true��Ԃ�
	bool Damage(int damage);
	Trunk* GetTrunk() { return m_trunk; }

	bool GetIsUsingState() { return m_isUsingState; }

	int GetNowHp() { return m_hp; }
	int GetMaxHp() { return m_maxHp; }
private:
	void UpdateRotation();
	void UpdateOBB();
	void MoveFromMoveVector();
	void CollisionOther();
	void ModelInit();
};

