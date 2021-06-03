#pragma once
#include "gameObject.h"

class Bullet :public GameObject
{
public:
	Bullet(){}
	Bullet(XMFLOAT3 f3Position);
	void Init();
	void Uninit();
	void Update();
	void Draw();

	static Bullet* Create(XMFLOAT3 f3Position, XMFLOAT3 f3Direction, float fSpeed);
	static void Destroy(Bullet* pBullet);
private:
	Model* m_model;
};