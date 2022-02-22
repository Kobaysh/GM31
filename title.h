#pragma once
#include "scene.h"

// タイトルシーン管理クラス
class Title:public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	float m_Timer = 0.0f;			// 経過時間
	float m_ParticleTimer = 0.0f;	// パーティクル発生間隔
	class Audio* m_DecisionSE;		// 決定SE
};

