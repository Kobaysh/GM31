/*==============================================================================

 キーロガー [keylogger.cpp]
 Author : Kobayashi Ryota
 Date : 2020/07/17
 --------------------------------------------------------------------------------*/
#include "main.h"
#include <d3dx9.h>
#include "keyboard.h"
#include "keylogger.h"


#define KEY_TYPE unsigned long
/*------------------------------------------------------------------------------
 グローバル変数宣言
------------------------------------------------------------------------------*/
// キー8以下なら
//typedef unsigned char KeyloggerType;

// 16
//typedef unsigned short KeyloggerType;

// 32
//typedef unsigned long KeyloggerType;

typedef KEY_TYPE KeyloggerType;
static KeyloggerType  g_currentKeyState = 0;	// そのフレームでのキーの状態保持用	
static KeyloggerType  g_prevKeyState = 0;		// 前フレームでのキーの状態保持用
static KeyloggerType  g_TriggerKeyState = 0;		// トリガー状態でのキーの状態保持用
static KeyloggerType  g_ReleaseKeyState = 0;	// リリース状態でのキーの状態保持用
static KeyloggerType* g_pRecordCurrentData = NULL;

static int g_keyloggerMode = 0;// 0:通常,1:記録,2:再生
static int g_RecordFrame = 0;
static int g_RecordPlayFrame = 0;
static int g_RecordFrameMax = 0;

// キーボードのキーからキーロガキーへの変換
static const Keyboard_Keys g_KKs[KL_MAX] = {
	KK_W,	    //KL_UP,						// 上移動
	KK_S,	    //KL_DOWN,						// 下移動
	KK_A,	    //KL_LEFT,						// 左移動
	KK_D,	    //KL_RIGHT,						// 右移動
	KK_U,		//KL_ATTACK,				 	// 攻撃キー
	KK_L,		//KL_DICISION 					// 決定キー
	KK_O,		//KL_GUARD,						// ガードキー
	KK_K,		//KL_CHANGENINGU,				// 忍具切り替えキー
	KK_E,		//KL_RISE,						// 上昇
	KK_Q,		//KL_fALL,						// 下降
	KK_ESCAPE,	//KL_CANCEL,					// キャンセル
	KK_R,		//KL_RESET,						// リセット
	KK_LEFT,	//KL_TURN_LEFT,					// 左回転
	KK_RIGHT,	//KL_TURN_RIGHT,				// 右回転
	KK_UP,		//KL_TURN_UP,					// 上回転
	KK_DOWN,	//KL_TURN_DOWN,					// 下回転
	KK_D9,		//KL_WIRE						// ワイヤフレーム切り替え
	KK_SPACE,	//KL_JUMP,						// サブ
	KK_D0,		//KL_CAMERA,					// カメラ切り替え
	KK_LEFTSHIFT, //	KL_DASH,				// ダッシュ
	KK_I		 //	KL_LOCKON,					// ロックオン
	//KL_MAX
};			   

//static Keyboard_State g_state = {};
 
// キーロガーモジュールの初期化
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
// キーロガーモジュールの終了処理
void KeyLogger_Fin(void)
{
	if (g_pRecordCurrentData) {
		free(g_pRecordCurrentData);
		g_pRecordCurrentData = NULL;
	}
}
// キーロガーモジュールの更新
void KeyLogger_Update(void)
{
	// 前フレームのキー状態を保存しておく
	g_prevKeyState = g_currentKeyState;
	// キーロガーモードに対応して動作変更
	if (g_keyloggerMode <= 1) {	//通常モード 記録モード
		g_currentKeyState = 0;
		// キーロガーキーの状態取得
		for (int i = 0; i < KL_MAX; i++) {
			if (Keyboard_IsKeyDown(g_KKs[i])) {
				g_currentKeyState |= 1u << i;
			}
		}
		// 記録モード
		if (g_keyloggerMode == 1) {	
			if (g_RecordFrame < g_RecordFrameMax) {
				g_pRecordCurrentData[g_RecordFrame++] = g_currentKeyState;
			}
		}
	}
	// 再生モード
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
// キー入力状態の取得

// キー入力状態の取得(押している間)
//
// 引数:
//
// 戻り値:押されていたらtrue
bool KeyLogger_Press(KeyloggerKey kl)
{
	return g_currentKeyState & (1u << (int)kl);
}

// キー入力状態の取得(押した瞬間)
//
// 引数:
//
// 戻り値:押したフレームのみtrue
bool KeyLogger_Trigger(KeyloggerKey kl)
{
	return g_TriggerKeyState & (1u << (int)kl);
}

// キー入力状態の取得(話した瞬間)
//
// 引数:
//
// 戻り値:離した瞬間だったらtrue
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
	// ファイルの先頭にデータ量を記録
	fwrite(&g_RecordFrame, sizeof(g_RecordFrame), 1, fp);
	// ファイルをデータを保存
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