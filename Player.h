#pragma once
#include "gameObject.h"

class Player : public GameObject
{
private:

	Model* m_Model;

	float m_speed;

	XMFLOAT3 m_front;
	XMFLOAT3 m_moveVector;
	int m_sign;



	int m_nowHp;					// ヒットポイント
	int m_maxHp;					// Maxヒットポイント
	int m_attackPower;				// 攻め力
	int m_nowTrunk;					// 体幹
	int m_maxtrunk;					// Max体幹
	int m_soundVolume;				// プレイヤーの出す音
	int m_nowWepon;					// 現在装備中の忍び義手の種類(番号)
	


	// 所持品
	// 装備中のアイテム
	// 技
	// 装備中の技
	// 技能

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Move();
	void Shoot();
	void VoidDimension();
	XMFLOAT3 GetMove()const { return m_moveVector; }
	XMFLOAT3* GetFront() { return &m_front; }
	float GetSpeed() { return m_speed; }
};

