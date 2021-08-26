#pragma once
#include "gameObject.h"
class Enemy : public GameObject
{
protected:
//	Model* m_model;
	int m_modelId;
	class Audio* m_explosionSE;
	class OBB* m_obb;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	OBB& GetObb() { return *m_obb; }
};

