/*==============================================================================

 �L�[���K�[ [keylogger.h]
 Author : Kobayashi Ryota
 Date : 2020/07/17
 --------------------------------------------------------------------------------*/
#ifndef _KEYLOGGER_H_
#define _KEYLOGGER_H_

// �L���L�[���K�[�L�[�񋓌^
typedef enum KeyloggerKey_tag {
	KL_UP,						// ��ړ�
	KL_DOWN,					// ���ړ�
	KL_LEFT,					// ���ړ�
	KL_RIGHT,					// �E�ړ�
	KL_ATTACK,					// �U���L�[
	KL_DICISION = KL_ATTACK,	// ����L�[
	KL_RISE,					// �㏸
	KL_FALL,					// ���~
	KL_CANCEL,					// �L�����Z��
	KL_RESET,					// ���Z�b�g
	KL_TURN_LEFT,				// ����]
	KL_TURN_RIGHT,				// �E��]
	KL_TURN_UP,					// ���]
	KL_TURN_DOWN,				// ����]
	KL_WIRE,					// ���C���t���[���؂�ւ�
	KL_FIRE,						// �T�u
	KL_CAMERA,					// �J�����؂�ւ�
	KL_TURBO,					// �^�[�{
	KL_MAX,						// �ő吔
}KeyloggerKey;

// �L�[���K�[���W���[���̏�����
void KeyLogger_Init(void);
// �L�[���K�[���W���[���̏I������
void KeyLogger_Fin(void);
// �L�[���K�[���W���[���̍X�V
void KeyLogger_Update(void);
// �L�[���͏�Ԃ̎擾

// �L�[���͏�Ԃ̎擾(�����Ă����)
//
// ����:
//
// �߂�l:������Ă�����true
bool KeyLogger_Press(KeyloggerKey kl);

// �L�[���͏�Ԃ̎擾(�������u��)
//
// ����:
//
// �߂�l:�������t���[���̂�true
bool KeyLogger_Trigger(KeyloggerKey kl);

// �L�[���͏�Ԃ̎擾(�b�����u��)
//
// ����:
//
// �߂�l:�������u�Ԃ�������true
bool KeyLogger_Release(KeyloggerKey kl);



void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void Keylogger_RecordLoad(void);
void Keylogger_RecordPlay(void);
bool Keylogger_IsRecordPlay(void);

#endif	// _KEYLOGGER_H_
