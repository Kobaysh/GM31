#include "behaviorTree.h"
#include "behaviorData.h"
#include "nodeBase.h"
#include "actionBase.h"
#include "enemy.h"
#include "enemyBehaviorIdle.h"
#include "enemyBehaviorLookingFor.h"
#include "enemyBehaviorRun.h"
#include "enemyBehavior.h"

const float EnemyBehavior::UPDATE_TIMER_AMOUNT = 0.01f;	// updateで増やすタイマーの量
const std::string EnemyBehavior::DATA_FILE_NAME;

void EnemyBehavior::Init()
{
	BehaviorTree* behavior = new BehaviorTree();
	behavior->AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, nullptr, nullptr);
	behavior->AddNode("Root", "LookingForPlayer", 0, BehaviorTree::SELECT_RULE::SEQENTIAL_LOOP, nullptr, nullptr);
	behavior->AddNode("LookingForPlayer", "Idle", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorIdle::GetInstance());
	behavior->AddNode("LookingForPlayer", "Lookingfor", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorLookingFor::GetInstance());
	behavior->AddNode("LookingForPlayer", "Run", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorRun::GetInstance());
	
	m_behaviorData = new BehaviorData();
	m_aiTree = behavior;
}

void EnemyBehavior::Uninit()
{
	delete m_aiTree;
	delete m_behaviorData;
}

void EnemyBehavior::Upadate(Enemy* pEnemy)
{

	if (!m_activeNode)
	{
		m_activeNode = m_aiTree->Inference(pEnemy, m_behaviorData);
	}

	if (m_activeNode)
	{
		m_timer += UPDATE_TIMER_AMOUNT;
		m_activeNode = m_aiTree->Run(pEnemy, m_activeNode, m_behaviorData, this);
	}
}

std::string EnemyBehavior::GetActiveNodeName()
{
	if (m_activeNode)
	{
		return	m_activeNode->GetName();
	} 
	else
	{
		return "Root";
	}
}

void EnemyBehavior::LoadDataFromCSV()
{

}
