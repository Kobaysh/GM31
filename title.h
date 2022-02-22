#pragma once


#include "scene.h"
class Title:public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	float m_Timer = 0.0f;
	float m_ParticleTimer = 0.0f;
	class Audio* m_DecisionSE;
};

