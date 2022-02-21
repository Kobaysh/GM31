#pragma once
#include <random>

class Utility
{
public:

	
	// �m����������֐�
	// numPer:0�`100�̊m��
	static bool Random(int numPer)
	{
		if (numPer < 0 || numPer > 100) return false;
		std::random_device rnd;     // �񌈒�I�ȗ���������𐶐�
		std::mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
		std::uniform_int_distribution<> rand100(0, 100);        // [0, 99] �͈͂̈�l����
		return (numPer >= rand100(mt));
	}

private:
	Utility() = delete;
	~Utility() = delete;
};