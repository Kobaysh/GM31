#pragma once
#include "gameObject.h"

class Player : public GameObject
{
private:

	Model* m_Model;



public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};

