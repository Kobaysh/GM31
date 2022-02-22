#pragma once
#include <string>
#include <unordered_map>

class MyGuiWindow;

class MyImGui
{
public:

	static void Init(HWND hwnd);
	static void Uninit();
	static void Update();
	static void SetNewFrame();
	static void StartRender();

	static void SetGuiWindow(const std::string& name, MyGuiWindow* window);
	static void DeleteGuiWindow(const std::string& name);

	static void SetSampleWindow();
	static void SetDebugWindow();
	static void SetDebugCameraWindow();
	static void SetDebugCollisionWindow();
	static void SetDebugPlayerWindow();

	static void SetIsShowAll(bool show) { m_IsShowAll = show; }
	static bool GetIsShowAll() { return m_IsShowAll; }
private:
	MyImGui() {}
	~MyImGui() {}
	static  bool m_IsShowAll;
	static std::unordered_map <std::string, class MyGuiWindow*> m_MyGuiWindows;
	 bool show_gui = true;
	 static bool m_IsCheckbox;

};

class MyGuiWindow
{
private:


protected:
	std::string m_Name;

public :
	MyGuiWindow(){}
	~MyGuiWindow(){}
	MyGuiWindow(const std::string& name):m_Name(name){}

	const char* GetWindowName() { return m_Name.data(); }
	const std::string GetWindowString() { return m_Name; }
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
};
