#pragma once
class MyImGui
{
public:


	static void Init(HWND hwnd);
	static void Uninit();
	static void Update();
	static void SetNewFrame();
	static void StartRender();

	static void SetSampleWindow();

//	static bool WndProcHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
private:
	MyImGui() {}
	~MyImGui() {}

	 bool show_gui = true;
	 bool checkbox;
};
