#pragma once
#include "gameObject.h"

class Rock : public GameObject
{
private:

//	Model* m_Model;
	int m_modelId;
	float m_speed;

	XMFLOAT3 m_front;
	XMFLOAT3 m_moveVector;
	int m_sign;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	XMFLOAT3 GetMove()const { return m_moveVector; }
	XMFLOAT3* GetFront() { return &m_front; }
};

