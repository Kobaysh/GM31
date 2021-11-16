#include <imgui.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemyGui.h"

void EnemyGui::Init()
{
	m_name  = "Enemy Window";
	MyImGui::SetGuiWindow(m_name, this);
}
void EnemyGui::Uninit()
{

}

void EnemyGui::Update()
{
	ImGui::SetNextWindowPos(ImVec2(720, 200), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(0.3f);
	static bool* p_open = nullptr;
	ImGuiWindowFlags window_flags = 0;
	{
		if (!ImGui::Begin(m_name.data() , p_open, window_flags))
		{
			ImGui::End();
			return;
		}



		ImGui::End();
	}
}
