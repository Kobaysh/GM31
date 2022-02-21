
#include "main.h"
#include <dinput.h>
#include "input.h"

#define MOUSE_ON_VALUE (0x80)


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
LPDIRECTINPUT8 Input::m_inputInterface;		
LPDIRECTINPUTDEVICE8 Input::m_mouseDevice;	
DIMOUSESTATE Input::m_currentMouseState;	
DIMOUSESTATE Input::m_prevMouseState;		
XMFLOAT2 Input::m_MousePos;					
bool Input::MOUSE_ACTIVE = false;

void Input::Init()
{

	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );

}

void Input::Init(HINSTANCE hInstance)
{
	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
		HRESULT hr = DirectInput8Create(hInstance, 
				DIRECTINPUT_VERSION,
				IID_IDirectInput8,
				(void**)&m_inputInterface,
				NULL);

	if (FAILED(hr))
	{
	// ���s
	}
	
	hr = m_inputInterface->CreateDevice(
			GUID_SysMouse,
			&m_mouseDevice,
			NULL
	);

	if (FAILED(hr))
	{
		// ���s
	}

	// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
	hr = m_mouseDevice->SetDataFormat(&c_dfDIMouse);

	if (FAILED(hr))
	{
		return ;
	}

/*	�t�H�A�O���E���h�ƃo�b�N�O���E���h�̓���
		���[�h	�萔	����
		�t�H�A�O���E���h	DISCL_FOREGROUND	�E�B���h�E���o�b�N�O���E���h�Ɉړ�������f�o�C�X�̎擾���ł��Ȃ�
		�o�b�N�O���E���h	DISCL_BACKGROUND	�E�B���h�E����A�N�e�B�u��Ԃł��f�o�C�X���擾�ł���


		�r���I�Ɣ�r���I�̓���
		���[�h	�萔	����
		�r���I	DISCL_EXCLUSIVE	���̃A�v���P�[�V�����͂��̓��̓f�o�C�X���擾�ł��Ȃ�
		��r���I	DISCL_NONEXCLUSIVE	���̃A�v���P�[�V�����ł����̂܂ܓ��̓f�o�C�X�̎擾���ł���
		*/

	if (FAILED(m_mouseDevice->SetCooperativeLevel(
		FindWindow(CLASS_NAME, nullptr),
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)
	))
	{
		// ���s
	}

	hr = m_mouseDevice->Acquire();
	if (FAILED(hr)) {
		return;
	}
	hr = m_mouseDevice->Poll();
	if (FAILED(hr)) {
		return;
	}


}

void Input::Uninit()
{

	if (m_mouseDevice) {
		m_mouseDevice->Unacquire();
		m_mouseDevice->Release();
	}
	if (m_inputInterface) {
		m_inputInterface->Release();
	}

}
void Input::Update()
{
	memcpy(m_OldKeyState, m_KeyState, 256);

	GetKeyboardState(m_KeyState);

	m_prevMouseState = m_currentMouseState;

	HRESULT hr = m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_currentMouseState);
	if (FAILED(hr)) {
		m_mouseDevice->Acquire();
		m_mouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_currentMouseState);
	}
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(GetWindow(), &p);
	m_MousePos.x = p.x;
	m_MousePos.y = p.y;


}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetMouseTrigger(MouseButton button_type)
{
	if (!(m_prevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		m_currentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}


	return false;
}

bool Input::GetMouseDown(MouseButton button_type)
{
	if ((m_prevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE) &&
		m_currentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE)
	{
		return true;
	}


	return false;
}

bool Input::GetMouseUp(MouseButton button_type)
{
	if (m_prevMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE &&
		!(m_currentMouseState.rgbButtons[button_type] & MOUSE_ON_VALUE))
	{
		return true;
	}
	return false;
}

XMFLOAT2 Input::GetMouseVelocity()
{
	return XMFLOAT2((float)m_currentMouseState.lX,(float)m_currentMouseState.lY);
}
