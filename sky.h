#pragma once
#include "gameObject.h"

// スカイドームクラス
class Sky : public GameObject
{
private:
	class Model* m_Model;	// モデル

	float m_Speed;			// 移動速度

	XMFLOAT3 m_Front;		// 前方向ベクトル
	XMFLOAT3 m_MoveVector;	// 移動方向
	int m_Sign;				// 符号

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	// 移動
	void Move();

	// 移動方向ゲッター
	XMFLOAT3 GetMove()const { return m_MoveVector; }

	// 前方向ゲッター
	XMFLOAT3* GetFront() { return &m_Front; }
};

