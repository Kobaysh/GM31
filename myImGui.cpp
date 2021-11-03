#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "myImGui.h"

void MyImGui::Init(HWND hwnd)
{
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
}

void MyImGui::Uninit()
{
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void MyImGui::Update()
{
	// フレーム開始
	MyImGui::SetNewFrame();

	// ここからウィンドウのセット
	MyImGui::SetSampleWindow();
}

void MyImGui::SetNewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void MyImGui::StartRender()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void MyImGui::SetSampleWindow()
{
	///*
	//   ウィンドウサイズを設定します。
	//   ImGuiCond_Once により、初回のみ設定されます。
	//   ImGuiCond_Always で、常に設定することもできます。
	//   */
	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_Once);

	bool show = true;
	float color_picker[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	{
	if (ImGui::Begin("MyImGui TitleBar Text", &show))
	{
		ImGui::Text(u8"今日は天気が良いです");

		//区切り線
		ImGui::Separator();

		ImGui::Text(u8"このように");
		ImGui::SameLine();
		ImGui::Text(u8"同じ行にコンテンツを追加することもできます");

		ImGui::Separator();

		ImGui::Checkbox(u8"チェックボックス", &show);

		ImGui::Separator();

		ImGui::ColorPicker4(u8"カラーピッカー", color_picker);

		//フレームレートを表示
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


	}
	ImGui::End();
	}
	{
		ImGui::SetNextWindowSize(ImVec2(320, 100), ImGuiCond_Once);
		ImGui::Begin("hoge", &show);
		//	ImGui::Begin("aaaa");
		ImGui::Text("fugafuga");
		ImGui::End(); 
	}
}

