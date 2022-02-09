#include <imgui.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "enemy.h"
#include "enemyState.h"
#include "enemyGui.h"
#include "trunk.h"

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
	ImGui::SetNextWindowSize(ImVec2(400, 200), ImGuiCond_Once);
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
					ImGui::Text("Position x:%.2fy:%.2fz:%.2f", enemyList[i]->GetPosition().x, enemyList[i]->GetPosition().y, enemyList[i]->GetPosition().z);
					ImGui::Text("Rotation x:%.2fy:%.2fz:%.2f", enemyList[i]->GetRotation().x, enemyList[i]->GetRotation().y, enemyList[i]->GetRotation().z);
					ImGui::Text("Forward x:%.2fy:%.2fz:%.2f", enemyList[i]->GetDirection()->Forward.x, enemyList[i]->GetDirection()->Forward.y, enemyList[i]->GetDirection()->Forward.z);
					if (ImGui::TreeNode("Enemy State"))
					{
						ImGui::Text(enemyList[i]->GetEnemyState()->GetStateName().c_str());
						ImGui::TreePop();
					}

					if (ImGui::TreeNode("Enemy HP"))
					{
						ImGui::Text("%d/%d",enemyList[i]->GetNowHp(), enemyList[i]->GetMaxHp());
						ImGui::TreePop();
					}
					if (ImGui::TreeNode("Enemy Trunk"))
					{
						ImGui::Text("%d/%d",enemyList[i]->GetTrunk()->GetNowTrunk(), enemyList[i]->GetTrunk()->GetMaxTrunk());
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
