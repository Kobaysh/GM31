#include "behaviorTree.h"
#include "nodeBase.h"
#include "actionBase.h"
#include "execJudgmentBase.h"
#include "enemy.h"
#include "behaviorData.h"

NodeBase* BehaviorTree::Inference(Enemy * pEnemy, BehaviorData * data)
{
	// データをリセットして開始
	data->Init();
	return m_root->Inference(pEnemy, data);
}

NodeBase* BehaviorTree::SequenceBack(NodeBase * sequenceNode, Enemy * pEnemy, BehaviorData * data)
{
	return sequenceNode->Inference(pEnemy, data);
}

void BehaviorTree::AddNode(std::string searchName, std::string entryName, int priority, SELECT_RULE selectRule, ExecJudgmentBase * judgment, ActionBase * action)
{
	if (searchName != "")
	{
		NodeBase* searchNode = m_root->SearchNode(searchName);
		if (searchNode)
		{
			NodeBase* sibling = searchNode->GetLastChiled();

			NodeBase* addNode = new NodeBase(entryName, searchNode, sibling, priority, selectRule, judgment, action, searchNode->GetHierarchNum() + 1);

			searchNode->AddChiled(addNode);
		}
	}
	else
	{
		if (!m_root)
		{
			m_root = new NodeBase(entryName, nullptr, nullptr, priority, selectRule, judgment, action, 1);
		}
	}
}

NodeBase* BehaviorTree::Run(Enemy * pEnemy, NodeBase * actionNode, BehaviorData * data)
{
	// ノード実行
	ActionBase::EXE_STATE state = actionNode->Run(pEnemy);
	// 正常終了なら
	if (state == ActionBase::EXE_STATE::COMPLETE)
	{
		// シーケンスの途中か判断
		NodeBase* sequenceNode = data->PopSequenceNode();

		// 途中なら継続、ないなら終了
		if (sequenceNode)
		{
			return SequenceBack(sequenceNode, pEnemy, data);
		}
		else
		{
			return nullptr;
		}
	}
	// 失敗なら終了
	else if (state == ActionBase::EXE_STATE::FAILED)
	{
		return nullptr;
	}

	// それ以外は現状維持
	return actionNode;
}
