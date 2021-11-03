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
	//ini�𐶐����Ȃ��悤��
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
	// �t���[���J�n
	MyImGui::SetNewFrame();

	// ��������E�B���h�E�̃Z�b�g
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
	//   �E�B���h�E�T�C�Y��ݒ肵�܂��B
	//   ImGuiCond_Once �ɂ��A����̂ݐݒ肳��܂��B
	//   ImGuiCond_Always �ŁA��ɐݒ肷�邱�Ƃ��ł��܂��B
	//   */
	ImGui::SetNextWindowSize(ImVec2(500, 600), ImGuiCond_Once);

	bool show = true;
	float color_picker[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	{
	if (ImGui::Begin("MyImGui TitleBar Text", &show))
	{
		ImGui::Text(u8"�����͓V�C���ǂ��ł�");

		//��؂��
		ImGui::Separator();

		ImGui::Text(u8"���̂悤��");
		ImGui::SameLine();
		ImGui::Text(u8"�����s�ɃR���e���c��ǉ����邱�Ƃ��ł��܂�");

		ImGui::Separator();

		ImGui::Checkbox(u8"�`�F�b�N�{�b�N�X", &show);

		ImGui::Separator();

		ImGui::ColorPicker4(u8"�J���[�s�b�J�[", color_picker);

		//�t���[�����[�g��\��
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

