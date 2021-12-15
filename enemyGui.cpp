#include <imgui.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyGui.h"

void EnemyGui::Init()
{
	m_name  = "Enemy Window";
//	MyImGui::SetGuiWindow(m_name, this);
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
		{
			if(ImGui::TreeNode("Enemy State"))
			{
				//ImGui::Text(EnemyState::enumChar_Enemy_State[m_enemy->GetEnemyState()->GetNowState()]);

				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
}
