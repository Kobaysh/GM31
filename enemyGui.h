#pragma once
#include "myImGui.h"

class EnemyGui : public MyGuiWindow
{
private:
//	const std::string m_windowName = "Enemy Window";
public:
	~EnemyGui() = delete;
	void Init()override;
	void Uninit()override;
	void Update()override;

};