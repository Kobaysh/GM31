#pragma once
#include <string>

class ActionBase;
class ExecJudgmentBase;
class NodeBase;
class Enemy;
class BehaviorData;

class BehaviorTree
{
public:
	//	選択ルール
	enum SELECT_RULE
	{
		NON,
		PRIORITY,		//	優先順位
		SEQUENCE,		//	シーケンス
		SEQENTIAL_LOOP,	//	シーケンシャルループ
		RANDOM,			//	ランダム
		ON_OFF,			//	オン・オフ
	};
public:
	BehaviorTree() :
		m_root(nullptr)
	{
	}
	//	実行ノードを推論
	NodeBase* Inference(Enemy* pEnemy, BehaviorData* data);

// シーケンスノードから推論開始
	NodeBase *SequenceBack(NodeBase *sequenceNode, Enemy* pEnemy, BehaviorData* data);

	// ノード追加
	void AddNode(std::string searchName, std::string entryName, int priority, SELECT_RULE selectRule, ExecJudgmentBase* judgment, ActionBase* action);

	// ツリー構造を表示
//	void PrintTree();

	// 実行
	NodeBase *Run(Enemy* pEnemy, NodeBase *actionNode, BehaviorData* data);

private:
	//	ルートノード
	NodeBase* m_root;
};