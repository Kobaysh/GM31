#pragma once
#include "myImGui.h"

class Enemy;

// �GGUI�N���X
class EnemyGui : public MyGuiWindow
{
public:
	EnemyGui(){}
	~EnemyGui() = delete;
	void Init()override;
	void Uninit()override;
	void Update()override;

	// �E�B���h�E�폜
	void Delete();
};