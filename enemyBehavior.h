#pragma once

class Enemy;
class EnmeyBehavior
{
private:
	class BehaviorTree* m_aiTree = nullptr;			// ビヘイビアツリー
	class BehaviorData* m_behaviorData = nullptr;	// ビヘイビアデータ
	class NodeBase* m_activeNode = nullptr;			// 実行中ノード

public:
	void Init(Enemy* pEnemy);
	void Uninit();
	void Upadate(Enemy* pEnemy);
};