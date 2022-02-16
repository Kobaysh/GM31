#pragma once
#include <string>
class Enemy;
class EnemyBehavior
{
private:
	class BehaviorTree* m_aiTree = nullptr;			// �r�w�C�r�A�c���[
	class BehaviorData* m_behaviorData = nullptr;	// �r�w�C�r�A�f�[�^
	class NodeBase* m_activeNode = nullptr;			// ���s���m�[�h

	float m_timer = 0.0f;
	static const float UPDATE_TIMER_AMOUNT;	// update�ő��₷�^�C�}�[�̗�
	static const std::string DATA_FILE_NAME;	// csv�t�@�C��
public:
	EnemyBehavior() { Init(); }
	void Init();
	void Uninit();
	void Upadate(Enemy* pEnemy);

	float GetTimer() { return m_timer; }
	void ResetTimer() { m_timer = 0.0f; }
	std::string GetActiveNodeName();
private:
	void LoadDataFromCSV();
};