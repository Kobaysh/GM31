#pragma once
#include "myImGui.h"

class Enemy;

// 敵GUIクラス
class EnemyGui : public MyGuiWindow
{
public:
	EnemyGui(){}
	~EnemyGui() = delete;
	void Init()override;
	void Uninit()override;
	void Update()override;

	// ウィンドウ削除
	void Delete();
};