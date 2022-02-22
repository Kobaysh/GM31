#pragma once
#define NOMINMAX
#include <xaudio2.h>
#include "gameObject.h"

// �I�[�f�B�I�Ǘ��N���X
class Audio : public GameObject
{
private:
	static IXAudio2*				m_XAudio;			// XAudio���W���[��
	static IXAudio2MasteringVoice*	m_MasteringVoice;	// �}�X�^�����O�{�C�X

	IXAudio2SourceVoice*	m_SourceVoice;	 // �\�[�X�{�C�X
	BYTE*					m_SoundData;	 // �����
	int						m_Length;		 // ����
	int						m_PlayLength;	 // �Đ�����


public:
	// ������
	static void InitMaster();

	//�@�I������
	static void UninitMaster();

	void Init() {};
	void Uninit();
	void Update() {};
	void Draw() {};

	// �ǂݍ���
	void Load(const char *FileName);

	// �Đ�
	void Play(float volume = 1.0f, bool Loop = false);


};

