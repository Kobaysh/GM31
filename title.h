#pragma once


#include "scene.h"
class Title:public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	float m_timer = 0.0f;
	float m_particleTimer = 0.0f;
};

