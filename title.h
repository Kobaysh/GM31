#pragma once
#include "scene.h"

// �^�C�g���V�[���Ǘ��N���X
class Title:public Scene
{
public:
	void Init() override;
	void Uninit() override;
	void Update() override;

private:
	float m_Timer = 0.0f;			// �o�ߎ���
	float m_ParticleTimer = 0.0f;	// �p�[�e�B�N�������Ԋu
	class Audio* m_DecisionSE;		// ����SE
};

