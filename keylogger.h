/*==============================================================================

 キーロガー [keylogger.h]
 Author : Kobayashi Ryota
 Date : 2020/07/17
 --------------------------------------------------------------------------------*/
#ifndef _KEYLOGGER_H_
#define _KEYLOGGER_H_

// 有効キーロガーキー列挙型
typedef enum KeyloggerKey_tag {
	KL_UP,						// 上移動
	KL_DOWN,					// 下移動
	KL_LEFT,					// 左移動
	KL_RIGHT,					// 右移動
	KL_ATTACK,					// 攻撃キー
	KL_DICISION = KL_ATTACK,	// 決定キー
	KL_RISE,					// 上昇
	KL_FALL,					// 下降
	KL_CANCEL,					// キャンセル
	KL_RESET,					// リセット
	KL_TURN_LEFT,				// 左回転
	KL_TURN_RIGHT,				// 右回転
	KL_TURN_UP,					// 上回転
	KL_TURN_DOWN,				// 下回転
	KL_WIRE,					// ワイヤフレーム切り替え
	KL_FIRE,						// サブ
	KL_CAMERA,					// カメラ切り替え
	KL_TURBO,					// ターボ
	KL_MAX,						// 最大数
}KeyloggerKey;

// キーロガーモジュールの初期化
void KeyLogger_Init(void);
// キーロガーモジュールの終了処理
void KeyLogger_Fin(void);
// キーロガーモジュールの更新
void KeyLogger_Update(void);
// キー入力状態の取得

// キー入力状態の取得(押している間)
//
// 引数:
//
// 戻り値:押されていたらtrue
bool KeyLogger_Press(KeyloggerKey kl);

// キー入力状態の取得(押した瞬間)
//
// 引数:
//
// 戻り値:押したフレームのみtrue
bool KeyLogger_Trigger(KeyloggerKey kl);

// キー入力状態の取得(話した瞬間)
//
// 引数:
//
// 戻り値:離した瞬間だったらtrue
bool KeyLogger_Release(KeyloggerKey kl);



void Keylogger_RecordStart(int frame_max);
void Keylogger_RecordEnd(void);
void Keylogger_RecordLoad(void);
void Keylogger_RecordPlay(void);
bool Keylogger_IsRecordPlay(void);

#endif	// _KEYLOGGER_H_
