#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "obb.h"
#include "camera.h"
#include "debugCamera.h"
#include "scene.h"
#include "gameObject.h"
#include "myImGui.h"
#include "player.h"
#include "trunk.h"

static float color_picker[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
static int dragint = 0;
std::unordered_map <std::string, class MyGuiWindow*> MyImGui::m_MyGuiWindows;
bool MyImGui::m_IsCheckbox = false;
#if defined (DEBUG) || defined (_DEBUG)
bool MyImGui::m_IsShowAll = true;
#else
bool MyImGui::m_IsShowAll = false;
#endif

void MyImGui::Init(HWND hwnd)
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();
	ImGui_ImplDX11_Init(Renderer::GetpDevice().Get(), Renderer::GetpDeviceContext().Get());
	ImGui_ImplWin32_Init(hwnd);
	//iniを生成しないように
	io.IniFilename = NULL;


	ImFontConfig config;
	config.MergeMode = true;
	io.Fonts->AddFontDefault();
	ImFont* font =
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\meiryo.ttc", 18.0f, &config, io.Fonts->GetGlyphRangesJapanese());
	IM_ASSERT(font != nullptr);
#else
	UNREFERENCED_PARAMETER(hwnd);
#endif
}

void MyImGui::Uninit()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	for (auto pair : m_MyGuiWindows)
	{
		pair.second->Uninit();
		delete pair.second;
	}
	m_MyGuiWindows.clear();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

void MyImGui::Update()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	// フレーム開始
	MyImGui::SetNewFrame();
	
	if (Input::GetKeyTrigger(VK_F3))
	{
		m_IsShowAll = m_IsShowAll ? false : true;
	}
	if (!m_IsShowAll) return;

	// ここからウィンドウのセット

	SetDebugWindow();
	for (auto pair : m_MyGuiWindows)
	{
		pair.second->Update();
	}
#endif
}

void MyImGui::SetNewFrame()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif
}

void MyImGui::StartRender()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}

void MyImGui::SetGuiWindow(const std::string & name, MyGuiWindow* window)
{
	auto it = m_MyGuiWindows.find(name);
	if (it != m_MyGuiWindows.end())
	{
		return;
	}
	m_MyGuiWindows[name] = window;
}

void MyImGui::DeleteGuiWindow(const std::string & name)
{
	auto it = m_MyGuiWindows.find(name);
	if (it != m_MyGuiWindows.end())
	{
		delete m_MyGuiWindows[name];
		m_MyGuiWindows.erase(name);
	}
}

void MyImGui::SetSampleWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_Once);

	bool show = false;
	bool show_demo_window = false;

	//{

	//	{
	//		ImGui::Begin("MyImGui TitleBar Text", &show);
	//		ImGui::Text(u8"今日は天気が良いです");

	//		//区切り線
	//		ImGui::Separator();

	//		ImGui::Text(u8"このように");
	//		ImGui::SameLine();
	//		ImGui::Text(u8"同じ行にコンテンツを追加することもできます");

	//		ImGui::Separator();

	//		ImGui::Checkbox(u8"チェックボックス", &m_IsCheckbox);

	//		ImGui::Separator();

	//		ImGui::ColorPicker4(u8"カラーピッカー", color_picker);

	//		//フレームレートを表示
	//		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//		ImGui::End();

	//	}

	//}
	//{
	//	ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
	//	ImGui::Begin("hoge", &show);
	//	
	//	ImGui::Text("fugafuga");
	//	ImGui::Separator();
	//
	//	ImGui::DragInt("dragint", &dragint);
	//	ImGui::End(); 
	//}

	ImGui::ShowDemoWindow(&show_demo_window);
#endif
}

void MyImGui::SetDebugWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(0.3f);
	static bool* p_open = nullptr;
	ImGuiWindowFlags window_flags = 0;
	{
		if (!ImGui::Begin("Debug Window", p_open, window_flags))
		{
			ImGui::End();
			return;
		}

		SetDebugCameraWindow();
		SetDebugCollisionWindow();
		SetDebugPlayerWindow();
		ImGui::End();
	}
#endif
}

void MyImGui::SetDebugCameraWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	if (ImGui::TreeNode("Camera"))
	{
		Camera* camera = ManagerT::GetScene()->GetGameObject<Camera>(GameObject::GOT_CAMERA);
		if (ImGui::TreeNode("Debug Camera"))
		{
			DebugCamera* debugCamera = ManagerT::GetScene()->GetGameObject<DebugCamera>(GameObject::GOT_CAMERA);
			bool debugCameraisActive = debugCamera->GetIsActive();
			ImGui::Checkbox("Debug Camera Active", &debugCameraisActive);
			debugCamera->SetIsActive(debugCameraisActive);
			debugCamera->ChangeMovableWithPlayer(debugCameraisActive);
			camera->SetIsActive(!debugCameraisActive);
			ImGui::TreePop();
		}

		//static bool cameraMovable = camera->GetMovable();
		//ImGui::Checkbox("Camera Movable", &cameraMovable);
		//if (camera->GetIsActive())
		//{
		//	camera->ChangeMovableWithPlayer(cameraMovable);
		//}
		ImGui::TreePop();
	}
#endif
}

void MyImGui::SetDebugCollisionWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	//ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);
	//ImGui::SetNextWindowBgAlpha(0.3f);
	//static bool* p_open = nullptr;
	//ImGuiWindowFlags window_flags = 0;
	//	window_flags = ImGuiWindowFlags_NoBackground;


	//if (!ImGui::Begin("Debug Collision", p_open, window_flags)) {
	//	ImGui::End();
	//	return;
	//}

//	bool debugShow = OBB::GetIsColShow();
//	ImGui::Checkbox("Collision Show", debugShow);
	if (ImGui::TreeNode("Collision"))
	{
		ImGui::Checkbox("Collision Show", &OBB::m_bIsDraw);
		ImGui::TreePop();
	}
//	OBB::SetIsColShow(debugShow);
//	ImGui::End();
#endif
}

void MyImGui::SetDebugPlayerWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || (RELEASE_ON_PLAY)
	if(ImGui::TreeNode("Player"))
	{
		Player* pPlayer = ManagerT::GetScene()->GetGameObject<Player>(GameObject::GameObject_Type::GOT_OBJECT3D);
		if (pPlayer)
		{
			ImGui::Text("HP:%d/%d", pPlayer->GetNowHp(), pPlayer->GetMaxHp());
			ImGui::Text("Trunk:%d/%d", pPlayer->GetTrunk()->GetNowTrunk(), pPlayer->GetTrunk()->GetMaxTrunk());
			ImGui::Text("timerGuard:%.2f", pPlayer->GetTimerGuard());
		}
		ImGui::TreePop();
	}
#endif
}
