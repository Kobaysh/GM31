#include "behaviorTree.h"
#include "nodeBase.h"
#include "actionBase.h"
#include "execJudgmentBase.h"
#include "enemy.h"

void BehabiorTree::AddNode(std::string searchName, std::string entryName, int priority, SELECT_RULE selectRule, ExecJudgmentBase * judgment, ActionBase * action)
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
