#pragma once
#include "gameObject.h"
class Enemy : public GameObject
{
protected:
//	Model* m_model;
	int m_modelId;
	class Audio* m_explosionSE;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

