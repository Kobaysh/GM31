#pragma once
#include <string>
class Enemy;
class EnemyBehavior
{
private:
	class BehaviorTree* m_aiTree = nullptr;			// ビヘイビアツリー
	class BehaviorData* m_behaviorData = nullptr;	// ビヘイビアデータ
	class NodeBase* m_activeNode = nullptr;			// 実行中ノード

	float m_timer = 0.0f;
	static const float UPDATE_TIMER_AMOUNT;	// updateで増やすタイマーの量
	static const std::string DATA_FILE_NAME;	// csvファイル
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