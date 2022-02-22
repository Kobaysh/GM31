#pragma once
#define NOMINMAX
#include <xaudio2.h>
#include "gameObject.h"

// オーディオ管理クラス
class Audio : public GameObject
{
private:
	static IXAudio2*				m_XAudio;			// XAudioモジュール
	static IXAudio2MasteringVoice*	m_MasteringVoice;	// マスタリングボイス

	IXAudio2SourceVoice*	m_SourceVoice;	 // ソースボイス
	BYTE*					m_SoundData;	 // 音情報
	int						m_Length;		 // 長さ
	int						m_PlayLength;	 // 再生時間


public:
	// 初期化
	static void InitMaster();

	//　終了処理
	static void UninitMaster();

	void Init() {};
	void Uninit();
	void Update() {};
	void Draw() {};

	// 読み込み
	void Load(const char *FileName);

	// 再生
	void Play(float volume = 1.0f, bool Loop = false);


};

