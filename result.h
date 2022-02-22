#pragma once
#include "scene.h"

// リザルトシーン管理クラス
class Result : public Scene
{
public:
	void Init()override;
	void Uninit()override;
	void Update()override;
};

