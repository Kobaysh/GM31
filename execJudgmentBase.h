#pragma once

class Enemy;

class ExecJudgmentBase
{
public:
	// ”»’èŠÖ”
	virtual bool Judgment(Enemy *enemy) = 0;
};