#pragma once

class Enemy;
class EnmeyBehavior
{
private:
	class BehaviorTree* m_aiTree = nullptr;			// �r�w�C�r�A�c���[
	class BehaviorData* m_behaviorData = nullptr;	// �r�w�C�r�A�f�[�^
	class NodeBase* m_activeNode = nullptr;			// ���s���m�[�h

public:
	void Init(Enemy* pEnemy);
	void Uninit();
	void Upadate(Enemy* pEnemy);
};