#pragma once
#include "gameObject.h"

class Player : public GameObject
{
private:

	Model* m_Model;

	float m_speed;

	XMFLOAT3 m_front;
	XMFLOAT3 m_moveVector;
	int m_sign;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Move();
	void Shoot();
	void VoidDimension();
	XMFLOAT3 GetMove()const { return m_moveVector; }
	XMFLOAT3* GetFront() { return &m_front; }
	float GetSpeed() { return m_speed; }
};

