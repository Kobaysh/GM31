#pragma once

class Enemy;

// ����C���^�[�t�F�[�X
class ExecJudgmentBase
{
public:
	// ����֐�
	virtual bool Judgment(Enemy *enemy) = 0;
};