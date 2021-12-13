#pragma once
#include <random>

class Utility
{
public:

	
	// 確率成功判定関数
	// numPer:0～100の確率
	static bool Random(int numPer)
	{
		if (numPer < 0 || numPer > 100) return false;
		std::random_device rnd;     // 非決定的な乱数生成器を生成
		std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
		std::uniform_int_distribution<> rand100(0, 100);        // [0, 99] 範囲の一様乱数
		return (numPer >= rand100(mt));
	}

private:
	Utility() = delete;
	~Utility() = delete;
};