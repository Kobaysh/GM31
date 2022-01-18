#pragma once
#include <vector>
#include <stack>
#include <map>
#include "behaviorTree.h"

class NodeBase;
class Enemy;

class BehaviorData
{
public:

	BehaviorData() { Init(); }

	// シーケンスノードのプッシュ
	void PushSequenceNode(NodeBase* node)
	{
		m_sequenceStack.push(node);
	}

	// シーケンスノードのポップ
	NodeBase* PopSequenceNode()
	{
		if (m_sequenceStack.empty())
		{
			return nullptr;
		}

		NodeBase* node = m_sequenceStack.top();

		if (node)
		{
			m_sequenceStack.pop();
		}
		return node;
	}

	// ノード使用判定
	bool IsNodeUsed(std::string name)
	{
		if (m_usedNodeMap.count(name) == 0)
		{
			return false;
		}
		return m_usedNodeMap[name];
	}

	// 使用済みノードに登録
	void EntryUsedNode(std::string	name)
	{
		m_usedNodeMap[name] = true;
	}

	// シーケンスステップのゲッター
	int GetSequenceStep(std::string name)
	{
		if (m_runSequenceStepMap.count(name) == 0)
		{
			m_runSequenceStepMap[name] = 0;
		}
		return m_runSequenceStepMap[name];
	}

	// シーケンスステップのセッター
	void SetSequenceStep(std::string name, int step)
	{
		m_runSequenceStepMap[name] = step;
	}

	// 初期化
	void Init()
	{
		m_runSequenceStepMap.clear();
		while (m_sequenceStack.size() > 0)
		{
			m_sequenceStack.pop();
		}
	}

	// 使用済みノードのリセット
	void ResetNodeUsed(std::vector<NodeBase*> *resetHierachy);

private:
	std::stack<NodeBase*> m_sequenceStack;				// シーケンスノードスタック
	std::map<std::string, int> m_runSequenceStepMap;	// 実行シーケンスのステップマップ
	std::map<std::string, bool> m_usedNodeMap;			// ノードの使用判定マップ
};