#pragma once
#include "scene.h"

// �Q�[���V�[���Ǘ��N���X
class Game: public Scene
{
public:
	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

private:
	bool m_IsGameClear;	// �Q�[���N���A������
};

