/*==============================================================================

 �L�[���K�[ [keylogger.cpp]
 Author : Kobayashi Ryota
 Date : 2020/07/17
 --------------------------------------------------------------------------------*/
#include "main.h"
#include <d3dx9.h>
#include "keyboard.h"
#include "keylogger.h"


#define KEY_TYPE unsigned long
/*------------------------------------------------------------------------------
 �O���[�o���ϐ��錾
------------------------------------------------------------------------------*/
// �L�[8�ȉ��Ȃ�
//typedef unsigned char KeyloggerType;

// 16
//typedef unsigned short KeyloggerType;

// 32
//typedef unsigned long KeyloggerType;

typedef KEY_TYPE KeyloggerType;
static KeyloggerType  g_currentKeyState = 0;	// ���̃t���[���ł̃L�[�̏�ԕێ��p	
static KeyloggerType  g_prevKeyState = 0;		// �O�t���[���ł̃L�[�̏�ԕێ��p
static KeyloggerType  g_TriggerKeyState = 0;		// �g���K�[��Ԃł̃L�[�̏�ԕێ��p
static KeyloggerType  g_ReleaseKeyState = 0;	// �����[�X��Ԃł̃L�[�̏�ԕێ��p
static KeyloggerType* g_pRecordCurrentData = NULL;

static int g_keyloggerMode = 0;// 0:�ʏ�,1:�L�^,2:�Đ�
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

// �L�[�{�[�h�̃L�[����L�[���K�L�[�ւ̕ϊ�
static const Keyboard_Keys g_KKs[KL_MAX] = {
	KK_W,	    //KL_UP,						// ��ړ�
	KK_S,	    //KL_DOWN,						// ���ړ�
	KK_A,	    //KL_LEFT,						// ���ړ�
	KK_D,	    //KL_RIGHT,						// �E�ړ�
	KK_U,		//KL_ATTACK,				 	// �U���L�[
	KK_L,		//KL_DICISION 					// ����L�[
	KK_O,		//KL_GUARD,						// �K�[�h�L�[
	KK_K,		//KL_CHANGENINGU,				// �E��؂�ւ��L�[
	KK_E,		//KL_RISE,						// �㏸
	KK_Q,		//KL_fALL,						// ���~
	KK_ESCAPE,	//KL_CANCEL,					// �L�����Z��
	KK_R,		//KL_RESET,						// ���Z�b�g
	KK_LEFT,	//KL_TURN_LEFT,					// ����]
	KK_RIGHT,	//KL_TURN_RIGHT,				// �E��]
	KK_UP,		//KL_TURN_UP,					// ���]
	KK_DOWN,	//KL_TURN_DOWN,					// ����]
	KK_D9,		//KL_WIRE						// ���C���t���[���؂�ւ�
	KK_SPACE,	//KL_JUMP,						// �T�u
	KK_D0,		//KL_CAMERA,					// �J�����؂�ւ�
	KK_LEFTSHIFT, //	KL_DASH,				// �_�b�V��
	KK_I		 //	KL_LOCKON,					// ���b�N�I��
	//KL_MAX
};			   

//static Keyboard_State g_state = {};
 
// �L�[���K�[���W���[���̏�����
void KeyLogger_Init(void)
{
	g_currentKeyState		= 0;
	g_prevKeyState			= 0;
	g_TriggerKeyState		= 0;
	g_ReleaseKeyState		= 0;

	g_keyloggerMode			= 0;
	g_pRecordCurrentData	= NULL;
	g_RecordFrame			= 0;
	g_RecordPlayFrame		= 0;
	g_RecordFrameMax		= 0;
}
// �L�[���K�[���W���[���̏I������
void KeyLogger_Fin(void)
{
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}
// �L�[���K�[���W���[���̍X�V
void KeyLogger_Update(void)
{
	// �O�t���[���̃L�[��Ԃ�ۑ����Ă���
	g_prevKeyState = g_currentKeyState;
	// �L�[���K�[���[�h�ɑΉ����ē���ύX
	if (g_keyloggerMode <= 1) {	//�ʏ탂�[�h �L�^���[�h
		g_currentKeyState = 0;
		// �L�[���K�[�L�[�̏�Ԏ擾
		for (int i = 0; i < KL_MAX; i++) {
			if (Keyboard_IsKeyDown(g_KKs[i])) {
				g_currentKeyState |= 1u << i;
			}
		}
		// �L�^���[�h
		if (g_keyloggerMode == 1) {	
			if (g_RecordFrame < g_RecordFrameMax) {
				g_pRecordCurrentData[g_RecordFrame++] = g_currentKeyState;
			}
		}
	}
	// �Đ����[�h
	else {
		if (g_RecordPlayFrame >= g_RecordFrame) {
			g_currentKeyState = 0;
		}
		else {
			g_currentKeyState = g_pRecordCurrentData[g_RecordPlayFrame++];
		}
	}

	g_TriggerKeyState = (g_prevKeyState ^ g_currentKeyState) & g_currentKeyState;
	g_ReleaseKeyState = (g_prevKeyState ^ g_currentKeyState) & g_prevKeyState;
}
// �L�[���͏�Ԃ̎擾

// �L�[���͏�Ԃ̎擾(�����Ă����)
//
// ����:
//
// �߂�l:������Ă�����true
bool KeyLogger_Press(KeyloggerKey kl)
{
	return g_currentKeyState & (1u << (int)kl);
}

// �L�[���͏�Ԃ̎擾(�������u��)
//
// ����:
//
// �߂�l:�������t���[���̂�true
bool KeyLogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u << (int)kl);
}

// �L�[���͏�Ԃ̎擾(�b�����u��)
//
// ����:
//
// �߂�l:�������u�Ԃ�������true
bool KeyLogger_Release(KeyloggerKey kl)
{
	return g_ReleaseKeyState & (1u << kl);
}


void Keylogger_RecordStart(int frame_max)
{
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
	}
	g_pRecordCurrentData = (KEY_TYPE*)malloc(sizeof(KEY_TYPE)* frame_max);
	g_keyloggerMode = 1;
	g_RecordFrame = 0;
	g_RecordFrameMax = frame_max;
}
void Keylogger_RecordEnd(void)
{
	if (!g_pRecordCurrentData) {
		return;
	}
	FILE* fp = fopen("keylogger.dat", "wb");
	// �t�@�C���̐擪�Ƀf�[�^�ʂ��L�^
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	// �t�@�C�����f�[�^��ۑ�
	fwrite(g_pRecordCurrentData, sizeof(g_pRecordCurrentData), g_RecordFrame, fp);
	fclose(fp);
	g_keyloggerMode = 0;
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}
void Keylogger_RecordLoad(void)
{
	FILE* fp = fopen("keylogger.dat", "rb");
	fread(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
	}
	g_pRecordCurrentData = (KeyloggerType*)malloc(sizeof(KeyloggerType)* g_RecordFrame);
	fread(g_pRecordCurrentData, sizeof(g_pRecordCurrentData), g_RecordFrame, fp);
	fclose(fp);
	g_keyloggerMode = 0;
}
void Keylogger_RecordPlay(void)
{
	g_RecordPlayFrame = 0;
	g_keyloggerMode = 2;
}
bool Keylogger_IsRecordPlay(void)
{
	if (g_keyloggerMode == 2) {
		return true;
	}
	return false;
}