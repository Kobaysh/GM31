#pragma once
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")

#define MOUSE_TRUE (false)

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static LPDIRECTINPUT8 m_inputInterface;		// DIRECTINPUT8のポインタ
	static LPDIRECTINPUTDEVICE8 m_mouseDevice;	// DIRECTINPUTDEVICE8のポインタ
	static DIMOUSESTATE m_currentMouseState;	// マウスの現在の入力情報
	static DIMOUSESTATE m_prevMouseState;		// マウスの前回の入力情報
	static XMFLOAT2 m_MousePos;					// マウス座標

	
public:
	static void Init();
	static void Init(HINSTANCE hInstance);
	static void Uninit();
	static void Update();

	enum MouseButton
	{
		Left,		
		Right,		
		Center,		
	};


	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static bool GetMouseDown(MouseButton button);
	static bool GetMouseUp(MouseButton button);

	static XMFLOAT2 GetMouseVelocity();
};
