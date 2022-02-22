#pragma once
#include <string>
class Enemy;
class BehaviorTree;

// 敵AIBehaviorTree管理クラス
class EnemyBehavior
{
private:
	class BehaviorTree* m_AiTree = nullptr;			// ビヘイビアツリー
	class BehaviorData* m_BehaviorData = nullptr;	// ビヘイビアデータ
	class NodeBase* m_ActiveNode = nullptr;			// 実行中ノード

	float m_Timer = 0.0f;
	static const float UPDATE_TIMER_AMOUNT;	// updateで増やすタイマーの量
	static const std::string DATA_FILE_NAME;	// csvファイル名
public:
	EnemyBehavior() { Init(); }
	EnemyBehavior(std::string fileName) { Init(fileName); }
	void Init();
	void Init(std::string fileName);
	void Uninit();
	void Upadate(Enemy* pEnemy);

	// タイマーゲッター
	float GetTimer() { return m_Timer; }
	
	// タイマーをリセット
	void ResetTimer() { m_Timer = 0.0f; }

	// 実行中のノードの名前取得
	std::string GetActiveNodeName();
private:

	// CSVファイルからデータを読み込む
	BehaviorTree* LoadDataFromCSV(BehaviorTree* pBehavior, std::string fileName);
};