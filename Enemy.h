#pragma once
#include "gameObject.h"
class Enemy : public GameObject
{
private:
	Model* m_model;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

