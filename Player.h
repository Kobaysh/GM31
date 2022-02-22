#pragma once
#include "gameObject.h"

// �v���C���[�N���X
class Player : public GameObject
{
private:
	class HpPlayer* m_HpBar = nullptr;				// HP�o�[
//	class Model* m_Model;
	class Audio* m_SlashSE= nullptr;				// �U��SE
	class OBB* m_Obb= nullptr;						// �����蔻��
	class OBB* m_ObbAttack= nullptr;				// �U������
	class AnimationModel*  m_Model= nullptr;		// ���f��
	class LockOnCircle* m_LockOnCircle = nullptr;	// ���b�N�I�����̉~
	class Trunk* m_Trunk;							// �̊�

	bool m_IsActive = true;							// �s���\��
	bool m_IsMovable = true;						// �ړ��\��
	bool m_IsAttack = false;						// �U������
	bool m_IsGuard = false;							// �K�[�h����
	bool m_Isjump = false;							// �W�����v����
	float m_JumpForce;								// �W�����v��
	float m_TimerAttack;							// �U�����^�C�}�[
	float m_TimerGuard;								// �K�[�h���^�C�}�[
	float m_LockOnRad;								// ���b�N�I������
	float m_Speed;									// ���x
	XMFLOAT3 m_MoveVector;							// �ړ�����
	int m_Sign;										// ����
	int m_NowHp;									// ����HP
	int m_MaxHp;									// �ő�HP
	int m_AttackPower;								// �U�ߗ�
	int m_SoundVolume;								// �v���C���[�̏o����
	int m_Frame;									// �o�߃t���[��
	std::string m_AnimationName;					// �A�j���[�V������
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �J���������ύX
	void ChangeCameraDir();

	// �ړ������Q�b�^�[
	XMFLOAT3 GetMove()const { return m_MoveVector; }
	
	// �ړ����x�Q�b�^�[
	float GetSpeed() { return m_Speed; }
	
	// �����蔻��Q�b�^�[
	OBB& GetObb() { return *m_Obb; }

	// �s���\��
	bool GetIsActive() const { return m_IsActive; }
	
	// �ړ��\��
	bool GetMovable() const { return m_IsMovable; }
	
	// �s���\�Z�b�^�[
	void SetIsActive(bool active) { m_IsActive = active; }
	
	// �ړ��\�Z�b�^�[
	void SetMovable(bool movable) { m_IsMovable = movable; }
	
	// �K�[�h����
	bool GetIsGuarding() { return m_IsGuard; }
	
	// �K�[�h���^�C�}�[�Q�b�^�[
	float GetTimerGuard() { return m_TimerGuard; }
	
	// �̊��Q�b�^�[
	Trunk* GetTrunk() { return m_Trunk; }
	
	// �_���[�W��^����
	bool Damage(int damage);
	
	// ����HP�Q�b�^�[
	int GetNowHp() { return m_NowHp; }
	
	// �ő�HP�Q�b�^�[
	int GetMaxHp() { return m_MaxHp; }
private:
	
	// ���f��������
	void ModelInit();
	
	// �����蔻��X�V
	void UpdateObb();
	
	// �ړ������ֈړ�
	void MoveFromMoveVector();
	
	// �A�j���[�V�����ύX
	void ChangeAnimation(const char* animationName);
	
	// �ړ�
	void Move();
	
	// �W�����v
	void Jump();
	
	// �U��
	void Slash();
	
	// ����
	void Shoot();
	
	// �K�[�h
	void Guard();
	
	// ���b�N�I��
	void LockOn();
	
	// �}�E�X�ƃL�[�{�[�h�ؑ�
	void MouseActive();
	
	// ���I�u�W�F�N�g�Ƃ̓����蔻��
	void CollisionOther();
};

