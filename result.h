#pragma once
#include "scene.h"

// ���U���g�V�[���Ǘ��N���X
class Result : public Scene
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
};

