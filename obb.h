#pragma once
#include "main.h"
#include "gameObject.h"

// 当たり判定管理クラス
class OBB : public GameObject
{
private:
	static ID3D11VertexShader*		m_VertexShader;			// 頂点シェーダー
	static ID3D11PixelShader*		m_PixelShader;			// ピクセルシェーダー
	static ID3D11InputLayout*		m_VertexLayout;			// 頂点レイアウト
															
	static const char* FILENAME_BLUE;						// テクスチャ名青
	static const char* FILENAME_RED;						// テクスチャ名赤
															 
	ID3D11Buffer*				m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11Buffer*				m_Indexbuffer = nullptr;	// インデックスバッファ
	ID3D11RasterizerState* m_RasterrizerState = nullptr;	// ラスタライザステート
																														
	bool m_IsDraw = false;									// 描画するか
	bool m_IsCollide = false;								// 当たっているか
	bool m_WasCollide = false;								// 当たったか
protected:
	XMFLOAT3 m_NormalDirect[3];								// 方向ベクトル
	float m_Length[3];										// 各軸方向の長さ

public:
	static bool m_IsDrawAll;					// 描画するか(全体)
	static bool m_IsDrawForwardRightUp;			// 方向成分を描画するか

	//　方向
	enum OBB_Direction {
		OBB_DX,		// X方向
		OBB_DY,		// Y方向
		OBB_DZ,		// Z方向
	};
	OBB(){
		m_NormalDirect[0] = XMFLOAT3(1.0f,0.0f,0.0f);
		m_NormalDirect[1] = XMFLOAT3(0.0f,1.0f,0.0f);
		m_NormalDirect[2] = XMFLOAT3(0.0f,0.0f,1.0f);
		m_Length[0] = 0.5f;
		m_Length[1] = 0.5f;
		m_Length[2] = 0.5f;
	}

	OBB(XMFLOAT3 pos, XMFLOAT3 size) {
		m_NormalDirect[0] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_NormalDirect[1] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_NormalDirect[2] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_Position = pos;
		m_Length[0] = size.x * 0.5f; 
		m_Length[1] = size.y * 0.5f;
		m_Length[2] = size.z * 0.5f;
		m_Scale = size;
	}
	OBB(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 size) {
		m_NormalDirect[0] = XMFLOAT3(1.0f, 0.0f, 0.0f);
		m_NormalDirect[1] = XMFLOAT3(0.0f, 1.0f, 0.0f);
		m_NormalDirect[2] = XMFLOAT3(0.0f, 0.0f, 1.0f);
		m_Position = pos;
		SetRotation(rot);
		m_Length[0] = size.x * 0.5f;
		m_Length[1] = size.y * 0.5f;
		m_Length[2] = size.z * 0.5f;
		m_Scale = size;
	}
	void SetScale(XMFLOAT3 size)override {
		m_Length[0] = size.x * 0.5f;
		m_Length[1] = size.y * 0.5f;
		m_Length[2] = size.z * 0.5f;
		m_Scale = size;
	}

	void Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;

	// 方向ゲッター
	XMFLOAT3 GetDirect(OBB_Direction elem) { return m_NormalDirect[elem]; }

	// 長さゲッター
	float GetLen_W(OBB_Direction elem) { return m_Length[elem]; }

	// 座標ゲッター
	XMFLOAT3 GetPos_W() { return m_Position; }

	// 回転率セッター
	void SetRotation(XMFLOAT3 rotationSpeed)override;
	void SetRotation(XMFLOAT3 rotation, XMFLOAT3 rotationSpeed);
	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right);
	void SetRotationFromForwardRightVector(XMFLOAT3 forward, XMFLOAT3 right, XMFLOAT3 rot);

	// 当たり判定関数
	static bool ColOBBs(OBB &obb1, OBB &obb2);

	// 描画するか(全体)
	static bool GetIsColShow() { return m_IsDrawAll; }

	// 描画状態セッター(全体)
	static void SetIsColShow(bool show) { m_IsDrawAll = show; }

	// 描画状態セッター(単体)
	void SetisDraw(bool isDraw) { m_IsDraw = isDraw; }

	// 当たり判定セッター
	void SetisCollide(bool isCollide) { m_IsCollide = isCollide; }
};