#pragma once
#include "gameObject.h"
class EnemyState;

// �G�N���X
class Enemy : public GameObject
{
public:
	// �G��ԃf�[�^
	struct EnemyStateData
	{
		float m_EyesightRad;		// ���o���a
		float m_EyesightAngle;		// ���o�p�x
		float m_HearingRad;			// ���o���a
		float m_MissedTime;			// �v���C���[������������
		bool m_IsDiscover;			// �v���C���[�𔭌����
		float m_CombatRad;			// �퓬���a
		EnemyStateData(float eyesight_rad, float eyesight_angle, float hearing_rad, float missed_time, float combat_rad):
			m_EyesightRad(eyesight_rad),
		m_EyesightAngle(eyesight_angle),
		m_HearingRad(hearing_rad),
		m_MissedTime(missed_time),
		m_CombatRad(combat_rad){}
	};
protected:
	class AnimationModel* m_Model;		// ���f��
	class Audio* m_explosionSE;			// ���USE
	class OBB* m_Obb;					// �����蔻��
	class EnemyState* m_State;			// ���
	class EnemyBehavior* m_Behavior;	// �r�w�C�r�A�c���[�Ǘ��I�u�W�F�N�g
	static class EnemyGui* m_EnemyGui;	// GUI�I�u�W�F�N�g
	class HpBar* m_HpBar;				// HP�o�[
	class Trunk* m_Trunk;				// �̊�
	class TrunkBar* m_TrunkBar;			// �̊��o�[
	XMFLOAT3 m_MoveVector;				// �ړ�����

	EnemyStateData m_StateData;			// ��ԃf�[�^
	XMFLOAT3 m_RotationSpeed;			// ��]���x
	float m_MoveSpeed;					// �ړ����x
	int m_NowHp;						// ����HP
	int m_MaxHp;						// �ő�HP
	bool m_IsUsingState = true;			// �X�e�[�g�}�V�[����AI�𑀍삵�Ă��邩

	int m_Frame;						// �o�߃t���[��
	std::string m_AnimationName;		// �A�j���[�V������

private:
	static const std::string VS_FILE_NAME;	// ���_�V�F�[�_�[��
	static const std::string PS_FILE_NAME;	// �s�N�Z���V�F�[�_�[��
public:
	Enemy();
	virtual void Init();
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 scale);
	virtual void Init(XMFLOAT3 pos, XMFLOAT3 rotation, XMFLOAT3 scale);
	void Uninit();
	void Update();
	void Draw();
	
	// OBB�C���X�^���X�Q�b�^�[
	OBB& GetObb() { return *m_Obb; }

	// �ړ����x�Q�b�^�[
	float GetMoveSpeed() { return m_MoveSpeed; }

	// �ړ������Z�b�^�[
	void SetMoveVector(XMFLOAT3 moveVector) { m_MoveVector = moveVector; }

	// ��]���x�Z�b�^�[
	void SetRotationSpeed(XMFLOAT3 rotationSpeed) { m_RotationSpeed = rotationSpeed; }

	// ��ԃf�[�^�Q�b�^�[
	EnemyStateData* GetEnemyStateData() { return &m_StateData; }

	// ��ԃQ�b�^�[
	class EnemyState* GetEnemyState() { return m_State; }
	
	// �r�w�C�r�A�c���[���Q�b�^�[
	std::string GetEnemyBehaviorName();

	// �|�W�V�����|�C���^�[�Q�b�^�[
	XMFLOAT3* GetpPosition() { return &m_Position; }
	
	// �_���[�W��^���AHP��0�ɂȂ�����true��Ԃ�
	bool Damage(int damage);

	// �̊��Q�b�^�[
	Trunk* GetTrunk() { return m_Trunk; }

	// �X�e�[�g�}�V�[���g�p����
	bool GetIsUsingState() { return m_IsUsingState; }

	// ����HP�Q�b�^�[
	int GetNowHp() { return m_NowHp; }

	// �ő�HP�Q�b�^�[
	int GetMaxHp() { return m_MaxHp; }

	// �A�j���[�V�������Q�b�^�[
	const std::string& GetAnimationName() const { return m_AnimationName; }

	// �A�j���[�V�������Z�b�^�[
	void SetAnimationName(const std::string& name) {
		m_AnimationName = name;
		ResetAnimationFrame(); }

	// �A�j���[�V�����t���[�����Z�b�g
	void ResetAnimationFrame() { m_Frame = 0; }
private:
	// ��]�X�V
	void UpdateRotation();
	
	// �����蔻��X�V
	void UpdateOBB();

	// �ړ������Ɉړ�
	void MoveFromMoveVector();

	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	void CollisionOther();

	// ���f��������
	void ModelInit();
};

