#pragma once
#include "gameObject.h"

// �X�J�C�h�[���N���X
class Sky : public GameObject
{
private:
	class Model* m_Model;	// ���f��

	float m_Speed;			// �ړ����x

	XMFLOAT3 m_Front;		// �O�����x�N�g��
	XMFLOAT3 m_MoveVector;	// �ړ�����
	int m_Sign;				// ����

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// �ړ�
	void Move();

	// �ړ������Q�b�^�[
	XMFLOAT3 GetMove()const { return m_MoveVector; }

	// �O�����Q�b�^�[
	XMFLOAT3* GetFront() { return &m_Front; }
};

