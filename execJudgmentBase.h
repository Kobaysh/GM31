#pragma once

class Enemy;

// 判定インターフェース
class ExecJudgmentBase
{
public:
	// 判定関数
	virtual bool Judgment(Enemy *enemy) = 0;
};