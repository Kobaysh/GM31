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

	static void SetSampleWindow();
	static void SetDebugWindow();
	static void SetDebugCameraWindow();
	static void SetDebugCollisionWindow();

	static void SetIsShowAll(bool show) { m_bIsShowAll = show; }
	static bool GetIsShowAll() { return m_bIsShowAll; }
private:
	MyImGui() {}
	~MyImGui() {}
	static  bool m_bIsShowAll;
	static std::unordered_map <std::string, class MyGuiWindow*> m_myGuiWindows;
	 bool show_gui = true;
	 static bool checkbox;

};

class MyGuiWindow
{
private:


protected:
	std::string m_name;

public :
	MyGuiWindow(){}
	~MyGuiWindow(){}
	MyGuiWindow(const std::string& name):m_name(name){}

	const char* GetWindowName() { return m_name.data(); }
	const std::string GetWindowString() { return m_name; }
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
};
