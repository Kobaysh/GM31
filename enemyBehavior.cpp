#include "behaviorTree.h"
#include "behaviorData.h"
#include "enemy.h"
#include "enemyBehaviorIdle.h"
#include "enemyBehaviorLookingFor.h"
#include "enemyBehaviorRun.h"
#include "enemyBehavior.h"

void EnmeyBehavior::Init(Enemy* pEnemy)
{
	BehaviorTree* behavior = new BehaviorTree();
	m_behaviorData = new BehaviorData();
	m_aiTree = behavior;
}

void EnmeyBehavior::Uninit()
{
	delete m_aiTree;
	delete m_behaviorData;
}

void EnmeyBehavior::Upadate(Enemy* pEnemy)
{
	if (!m_activeNode)
	{
		m_activeNode = m_aiTree->Inference(pEnemy, m_behaviorData);
	}

	if (m_activeNode)
	{
		m_activeNode = m_aiTree->Run(pEnemy, m_activeNode, m_behaviorData);
	}
}
