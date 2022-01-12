#include "execJudgmentBase.h"
#include "nodeBase.h"

bool NodeBase::Judgment(Enemy * pEnemy)
{
	//	判定クラスを持っていれば実行、なければtrue
	if (m_execJudgment)
	{
		return m_execJudgment->Judgment(pEnemy);
	}
	return true;
}

NodeBase * NodeBase::SelectPriority(std::vector<NodeBase*>* list)
{
	NodeBase* selectNode = nullptr;
	int priority = -1000;

	//  優先順位が一番高いノードを探索
	for (auto node : *list)
	{
		if (priority < node->GetPriority())
		{
			selectNode = node;
			priority = node->GetPriority();
		}
	}

	return selectNode;
}

NodeBase * NodeBase::SelectRandom(std::vector<NodeBase*>* list)
{
	int selectNum = rand() % list->size();

	return (*list)[selectNum];
}

NodeBase * NodeBase::SearchNode(std::string searchName)
{
	if (m_name == searchName)
	{
		return this;
	}
	else
	{
		for (auto child : m_child)
		{
			NodeBase * temp = child->SearchNode(searchName);
			if (temp != nullptr)
			{
				return temp;
			}
		}
	}
	return nullptr;
}

ActionBase::EXE_STATE NodeBase::Run(Enemy * pEnemy)
{
	// アクションノードが存在してるなら結果を、なければ失敗を返す
	if (m_action)
	{
		return m_action->Run(pEnemy);
	}

	return ActionBase::FAILED;
}
