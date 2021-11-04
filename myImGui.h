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

	static void SetIsShowAll(bool show) { m_bIsShowAll = show; }
	static bool GetIsShowAll() { return m_bIsShowAll; }
private:
	MyImGui() {}
	~MyImGui() {}
	static  bool m_bIsShowAll;

	 bool show_gui = true;
	 static bool checkbox;
};
