#pragma once
#include "myImGui.h"

class Enemy;

class EnemyGui : public MyGuiWindow
{
private:
//	const std::string m_windowName = "Enemy Window";
	Enemy* m_enemy;
public:
//	EnemyGui(){}
	EnemyGui(Enemy* enemy) :m_enemy(enemy){}
	~EnemyGui() = delete;
	void Init()override;
	void Uninit()override;
	void Update()override;

};