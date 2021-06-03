#pragma once
#include "gameObject.h"
class Enemy : public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Model* m_model;
};

