#pragma once
#include "gameObject.h"

class Sky : public GameObject
{
private:

	class Model* m_Model;

	float m_Speed;

	XMFLOAT3 m_Front;
	XMFLOAT3 m_MoveVector;
	int m_Sign;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Move();
	XMFLOAT3 GetMove()const { return m_MoveVector; }
	XMFLOAT3* GetFront() { return &m_Front; }
};

