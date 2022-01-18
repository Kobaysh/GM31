#pragma once

class Enemy;

class ExecJudgmentBase
{
public:
	virtual bool Judgment(Enemy *enemy) = 0;
};