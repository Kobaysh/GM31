#pragma once
#include "gameObject.h"

// �J�����N���X
class Camera : public GameObject
{

protected:
	XMFLOAT3 m_Target;						// �^�[�Q�b�g
	bool m_IsActive;						// �g�p�\��
	bool m_IsMovable;						// �ړ��\��
	bool m_IsLock;							// ���b�N�I������
	XMFLOAT4X4 m_ViewMatrix;				// �r���[�}�g���N�X
	XMFLOAT4X4 m_ProjectionMatrix;			// �v���W�F�N�V�����}�g���N�X
	XMFLOAT3 m_Move;						// �ړ�����
	XMFLOAT3* m_LockTargetPos;				// �^�[�Q�b�g���W
											
	static float m_RoutationalSpeed;		// ��]���x
	float m_MoveSpeed;						// �ړ����x
	const static float m_CameraSpeedFirst;	// �J�����������x
	const static float m_AtLength;			// �^�[�Q�b�g�܂ł̋���
public:
	Camera():m_IsMovable(false),m_IsActive(false){}
	Camera(bool movable):m_IsMovable(movable),m_IsActive(false){}
	Camera(bool active, bool movable):m_IsActive(active),m_IsMovable(movable){}
	virtual void Init();
	virtual void Init(bool active, bool movable = false);
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	// �g�p�\��
	virtual bool GetIsActive() { return m_IsActive; }

	// �ړ��\��
	virtual bool GetMovable() { return m_IsMovable; }

	// �g�p�\�Z�b�^�[
	virtual void SetIsActive(bool active) { m_IsActive = active; }

	// �ړ��\�Z�b�^�[
	virtual void SetMovable(bool movable) { m_IsMovable = movable; }

	// �g�p�\&�ړ��\�Z�b�^�[
	virtual void SetActiveMovable(bool set) { SetIsActive(set); SetMovable(set); }

	// �r���[�}�g���N�X�Q�b�^�[
	virtual XMFLOAT4X4* GetView() { return &m_ViewMatrix; }

	// ������J�����O
	virtual bool CheckView(XMFLOAT3 pos, XMFLOAT3 scale = XMFLOAT3(1.0f,1.0f,1.0f));
	
	// �ړ������Q�b�^�[
	virtual XMFLOAT3* GetMove() { return &m_Move; }

	// �ړ����x�Q�b�^�[
	virtual float GetSpeed();

	// �v���C���[�Ɠ����Ɉړ��\��Ԃ�ύX
	virtual void ChangeMovableWithPlayer();

	// �v���C���[�Ɠ����Ɉړ��\��Ԃ�ύX
	virtual void ChangeMovableWithPlayer(bool movable);

	// �����ύX
	virtual void ChangeDir(float angle, bool isRight);

	// ���b�N�I�����W�Z�b�^�[
	void SetLockTarget(XMFLOAT3* pos) { m_LockTargetPos = pos; }

	// ���b�N�I����ԃZ�b�^�[
	void SetIsLock(bool lock) { m_IsLock = lock; }
	
	// ���b�N�I����ԃQ�b�^�[
	bool GetIsLock(){return m_IsLock;}
};

