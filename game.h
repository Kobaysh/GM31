#pragma once
#include "scene.h"

// ゲームシーン管理クラス
class Game: public Scene
{
public:
	void Init() override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

private:
	bool m_IsGameClear;	// ゲームクリアしたか
};

