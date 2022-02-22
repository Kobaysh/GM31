#pragma once
#include "myImGui.h"

class Enemy;

class EnemyGui : public MyGuiWindow
{
private:
//	const std::string m_windowName = "Enemy Window";
//	Enemy* m_Enemy;
public:
	EnemyGui(){}
//	EnemyGui(Enemy* enemy) :m_Enemy(enemy){}
	~EnemyGui() = delete;
	void Init()override;
	void Uninit()override;
	void Update()override;
	void Delete();
};