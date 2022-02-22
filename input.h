#pragma once
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")


//#define MOUSE_ACTIVE (true)

// 入力処理クラス
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

	static bool  MOUSE_ACTIVE;
public:
	static void Init();
	static void Init(HINSTANCE hInstance);
	static void Uninit();
	static void Update();

	enum MouseButton
	{
		Left,		// 左クリック
		Right,		// 右クリック
		Center,		// ホイールクリック
	};

	// マウス使用中か
	static bool GetMouseActive() { return MOUSE_ACTIVE; }

	// マウス使用状態セッター
	static void SetMouseActive(bool active) { MOUSE_ACTIVE = active; }

	// キー入力取得(押下中)
	static bool GetKeyPress( BYTE KeyCode );

	// キー入力取得(押下瞬間)
	static bool GetKeyTrigger( BYTE KeyCode );

	// マウス入力取得(押下瞬間)
	static bool GetMouseTrigger(MouseButton button);

	// マウス入力取得(押下中)
	static bool GetMouseDown(MouseButton button);

	// マウス入力取得(離す瞬間)
	static bool GetMouseUp(MouseButton button);

	// マウス移動値ゲッター
	static XMFLOAT2 GetMouseVelocity();
};
