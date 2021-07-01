#pragma once

#include "singleton.h"
#include "scene.h"
class Title:SingletonT<Title>, Scene
{
public:
	void Init() override;
	void Uninit() override;
};

