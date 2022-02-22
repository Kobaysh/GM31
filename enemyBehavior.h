#pragma once
#include <string>
class Enemy;
class BehaviorTree;

// �GAIBehaviorTree�Ǘ��N���X
class EnemyBehavior
{
private:
	class BehaviorTree* m_AiTree = nullptr;			// �r�w�C�r�A�c���[
	class BehaviorData* m_BehaviorData = nullptr;	// �r�w�C�r�A�f�[�^
	class NodeBase* m_ActiveNode = nullptr;			// ���s���m�[�h

	float m_Timer = 0.0f;
	static const float UPDATE_TIMER_AMOUNT;	// update�ő��₷�^�C�}�[�̗�
	static const std::string DATA_FILE_NAME;	// csv�t�@�C����
public:
	EnemyBehavior() { Init(); }
	EnemyBehavior(std::string fileName) { Init(fileName); }
	void Init();
	void Init(std::string fileName);
	void Uninit();
	void Upadate(Enemy* pEnemy);

	// �^�C�}�[�Q�b�^�[
	float GetTimer() { return m_Timer; }
	
	// �^�C�}�[�����Z�b�g
	void ResetTimer() { m_Timer = 0.0f; }

	// ���s���̃m�[�h�̖��O�擾
	std::string GetActiveNodeName();
private:

	// CSV�t�@�C������f�[�^��ǂݍ���
	BehaviorTree* LoadDataFromCSV(BehaviorTree* pBehavior, std::string fileName);
};