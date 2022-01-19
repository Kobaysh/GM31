#include <imgui.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "enemy.h"
#include "enemyState.h"
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
	std::vector<Enemy*> enemyList = ManagerT::GetScene()->GetGameObjects<Enemy>(GameObject::GameObject_Type::GOT_OBJECT3D);
	{
		if (!ImGui::Begin(m_name.data() , p_open, window_flags))
		{
			ImGui::End();
			return;
		}
		{
			for (unsigned int i = 0; i < enemyList.size(); i++)
			{
				if (ImGui::TreeNode("enmey:%d","Enemy:%d", i + 1))
				{

					if (ImGui::TreeNode("Enemy State"))
					{
						ImGui::Text(enemyList[i]->GetEnemyState()->GetStateName().c_str());
						ImGui::TreePop();
					}
					ImGui::TreePop();
				}
			}
			//if (ImGui::TreeNode("Enemy State"))
			//{
			//	ImGui::Text(m_enemy->GetEnemyState()->GetStateName().c_str());

			//	ImGui::TreePop();
			//}
		}
		ImGui::End();
	}
}

void EnemyGui::Delete()
{
	MyImGui::DeleteGuiWindow(m_name);
}
