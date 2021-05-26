#pragma once
#include "gameObject.h"

class Bullet :public GameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
private:

};