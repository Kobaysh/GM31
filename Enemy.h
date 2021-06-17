#pragma once
#include "gameObject.h"
class Enemy : public GameObject
{
protected:
	Model* m_model;
	int m_modelId;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

