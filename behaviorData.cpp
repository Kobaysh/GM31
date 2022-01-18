#include "behaviorData.h"
#include "nodeBase.h"
#include "enemy.h"

void BehaviorData::ResetNodeUsed(std::vector<NodeBase*>* resetHierachy)
{
	for (auto node : *resetHierachy)
	{
		m_usedNodeMap[node->GetName()] = false;
	}
}
