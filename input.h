#pragma once
#include <dinput.h>
#pragma comment(lib, "dinput8.lib")


//#define MOUSE_ACTIVE (true)

// ���͏����N���X
class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static LPDIRECTINPUT8 m_inputInterface;		// DIRECTINPUT8�̃|�C���^
	static LPDIRECTINPUTDEVICE8 m_mouseDevice;	// DIRECTINPUTDEVICE8�̃|�C���^
	static DIMOUSESTATE m_currentMouseState;	// �}�E�X�̌��݂̓��͏��
	static DIMOUSESTATE m_prevMouseState;		// �}�E�X�̑O��̓��͏��
	static XMFLOAT2 m_MousePos;					// �}�E�X���W

	static bool  MOUSE_ACTIVE;
public:
	static void Init();
	static void Init(HINSTANCE hInstance);
	static void Uninit();
	static void Update();

	enum MouseButton
	{
		Left,		// ���N���b�N
		Right,		// �E�N���b�N
		Center,		// �z�C�[���N���b�N
	};

	// �}�E�X�g�p����
	static bool GetMouseActive() { return MOUSE_ACTIVE; }

	// �}�E�X�g�p��ԃZ�b�^�[
	static void SetMouseActive(bool active) { MOUSE_ACTIVE = active; }

	// �L�[���͎擾(������)
	static bool GetKeyPress( BYTE KeyCode );

	// �L�[���͎擾(�����u��)
	static bool GetKeyTrigger( BYTE KeyCode );

	// �}�E�X���͎擾(�����u��)
	static bool GetMouseTrigger(MouseButton button);

	// �}�E�X���͎擾(������)
	static bool GetMouseDown(MouseButton button);

	// �}�E�X���͎擾(�����u��)
	static bool GetMouseUp(MouseButton button);

	// �}�E�X�ړ��l�Q�b�^�[
	static XMFLOAT2 GetMouseVelocity();
};
