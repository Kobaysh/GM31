#pragma once
#include "gameObject.h"

// フェード管理クラス
class Fade : public GameObject
{
public:
	// フェードタイプ
	enum FadeType
	{
		FADE_NONE = -1,
		FADE_IN,	// フェードイン
		FADE_OUT,	// フェードアウト
		FADE_MAX
	};

	void Init();
	void Uninit();
	void Update();
	void Draw();
	
	// フェード状態セット
	static void SetFade(FadeType type);

	// フェードタイプゲッター
	static FadeType GetFadeType();

private:

	static FadeType m_FadeType;				// フェードタイプ 
	static float m_FadeAlpha;				// フェードα値

	ID3D11Buffer* m_VertexBuffer = nullptr;	// 頂点バッファ
};

