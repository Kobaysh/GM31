#pragma once
#include "gameObject.h"
#include "playerState.h"

class Player : public GameObject
{
private:


	class PlayerState  m_playerState;
//	class Model* m_Model;
	class Audio* m_shotSE;
	class OBB* m_obb;
	class AnimationModel*  m_Model;

	bool m_isActive = true;
	bool m_movable = true;
	float m_speed;

	XMFLOAT3 m_front;
	XMFLOAT3 m_up;

	XMFLOAT3 m_moveVector;
	int m_sign;

	bool m_isjump = false;
	float m_jumpForce;

	int m_nowHp;					// �q�b�g�|�C���g
	int m_maxHp;					// Max�q�b�g�|�C���g
	int m_attackPower;				// �U�ߗ�

	int m_soundVolume;				// �v���C���[�̏o����
	int m_nowWepon;					// ���ݑ������̔E�ы`��̎��(�ԍ�)
	
	int m_frame;
	std::string m_animationName;

	// �����i
	// �������̃A�C�e��
	// �Z
	// �������̋Z
	// �Z�\

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Move();
	void Jump();
	void Shoot();
	void CollisionOther();
	void VoidDimension();
	void ChangeCameraDir();
	XMFLOAT3 GetMove()const { return m_moveVector; }
	XMFLOAT3* GetFront() { return &m_front; }
	float GetSpeed() { return m_speed; }
	OBB& GetObb() { return *m_obb; }

	bool GetIsActive() const { return m_isActive; }
	bool GetMovable() const { return m_movable; }
	void SetIsActive(bool active) { m_isActive = active; }
	void SetMovable(bool movable) { m_movable = movable; }
};

