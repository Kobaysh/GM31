#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "obb.h"
#include "camera.h"
#include "Scene.h"
#include "gameObject.h"
#include "myImGui.h"

static float color_picker[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
static int dragint = 0;
bool MyImGui::checkbox = false;
bool MyImGui::m_bIsShowAll = false;

void MyImGui::Init(HWND hwnd)
{
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
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
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif
}

void MyImGui::Update()
{
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
	// フレーム開始
	MyImGui::SetNewFrame();
	
	if (Input::GetKeyPress(VK_LCONTROL) && Input::GetKeyTrigger(VK_RCONTROL))
	{
		m_bIsShowAll = m_bIsShowAll ? false : true;
	}
	if (!m_bIsShowAll) return;

	// ここからウィンドウのセット

	SetDebugWindow();
#endif
}

void MyImGui::SetNewFrame()
{
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
#endif
}

void MyImGui::StartRender()
{
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
}

void MyImGui::SetSampleWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
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

	//		ImGui::Checkbox(u8"チェックボックス", &checkbox);

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
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
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

		if (ImGui::TreeNode("Camera"))
		{
			Camera* camera = ManagerT::GetScene()->GetGameObject<Camera>(GameObject::GOT_CAMERA);
			static bool cameraMovable = camera->GetMovable();
			ImGui::Checkbox("Camera Movable", &cameraMovable);
			camera->SetMovale(cameraMovable);
			ImGui::TreePop();
		}
		SetDebugCollisionWindow();
		ImGui::End();
	}
#endif
}

void MyImGui::SetDebugCollisionWindow()
{
#if defined (DEBUG) || defined (_DEBUG) || defined(RELEASE_ON_PLAY)
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

