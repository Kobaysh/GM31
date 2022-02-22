#pragma once
#include "main.h"
#include "renderer.h"

#define GRAVITY (0.098f * 0.3f)

// ゲームオブジェクトインターフェース
class GameObject
{
public:
	// オブジェクトの状態
	enum GameObject_State 
	{
		GOS_NONE = -1,
		GOS_ACTIVE,
		GOS_PAUSE,
		GOS_DEAD,
	};
	// オブジェクトの種類
	enum GameObject_Type 
	{
		GOT_NONE = -1,
		GOT_CAMERA,
		GOT_OBJECT3D,
		GOT_OBJECT2D,
		GOT_MAX,
	};
	// 方向
	struct GameObject_Direction
	{
		XMFLOAT3 Forward;
		XMFLOAT3 Right;
		XMFLOAT3 Up;
	};
protected:

	XMFLOAT3 m_Position;								// 座標
	XMFLOAT3 m_Rotation;								// 回転
	XMFLOAT3 m_Scale;									// 拡大率
	GameObject_Direction m_Direction;					// 方向
														
	GameObject_State m_GOState = GOS_ACTIVE;			// 状態
														 
	ID3D11VertexShader*		m_VertexShader = nullptr;	// 頂点シェーダー
	ID3D11PixelShader*		m_PixelShader = nullptr;	// ピクセルシェーダー
	ID3D11InputLayout*		m_VertexLayout = nullptr;	// 頂点レイアウト	

public:
	
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	// 座標セッター
	void SetPosition(XMFLOAT3 pos) { m_Position = pos; }

	// 回転率セッター
	virtual void SetRotation(XMFLOAT3 rot) { m_Rotation = rot; }

	// 拡大率セッター
	virtual void SetScale(XMFLOAT3 scale) { m_Scale = scale; }

	// 座標ゲッター
	XMFLOAT3 GetPosition() { return m_Position; }

	// 回転率ゲッター
	XMFLOAT3 GetRotation() { return m_Rotation; }
	
	// 方向ゲッター
	GameObject_Direction* GetDirection() { return &m_Direction; }

	// 死亡状態にセット
	void SetDead() { m_GOState = GOS_DEAD; }

	// 死亡状態ならオブジェクト削除
	bool Destroy() {
		if (m_GOState == GOS_DEAD) {
			Uninit();
			delete this;
			return true;
		}
		else {
			return false;
		}
	}

	// ピクセルシェーダー作成
	void SetPShader(const char* pFileName){
		Renderer::CreatePixelShader(&m_PixelShader, pFileName);
	}

	// 頂点シェーダー作成
	void SetVShader(const char* pFileName) {
		Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, pFileName);
	}
};

