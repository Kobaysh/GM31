#pragma once
#include "gameObject.h"

class Player : public GameObject
{
private:

	Model* m_Model;

	float m_speed;

	bool m_bTrriger;

	XMFLOAT3 m_front;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Move();
	void Shoot();

};

