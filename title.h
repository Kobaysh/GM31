#pragma once


#include "scene.h"
class Title:public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};

