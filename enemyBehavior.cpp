#include "behaviorTree.h"
#include "behaviorData.h"
#include "nodeBase.h"
#include "actionBase.h"
#include "enemy.h"
#include "enemyBehaviorIdle.h"
#include "enemyBehaviorLookingFor.h"
#include "enemyBehaviorRun.h"
#include "enemyBehavior.h"
#include <fstream>


const float EnemyBehavior::UPDATE_TIMER_AMOUNT = 0.01f;	// update�ő��₷�^�C�}�[�̗�
const std::string EnemyBehavior::DATA_FILE_NAME;

// �A�N�V�������O
enum ActionInstanceName
{
	Behavior_Idle,
	Behavior_LookingFor,
	Behavior_Run,
};

// �ǂݍ��ރf�[�^
struct AiData
{
	std::string ParentName;
	std::string EntryName;
	int Priority;
	int SelectRule;
	int JudgeNum;
	int ActionNum;
};

// ������
void EnemyBehavior::Init()
{
	BehaviorTree* behavior = new BehaviorTree();
	behavior->AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, nullptr, nullptr);
	behavior->AddNode("Root", "LookingForPlayer", 0, BehaviorTree::SELECT_RULE::SEQENTIAL_LOOP, nullptr, nullptr);
	behavior->AddNode("LookingForPlayer", "Idle", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorIdle::GetInstance());
	behavior->AddNode("LookingForPlayer", "Lookingfor", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorLookingFor::GetInstance());
	behavior->AddNode("LookingForPlayer", "Run", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorRun::GetInstance());
//	behavior = this->LoadDataFromCSV(behavior, "asset\\csv\\test.csv");

	m_behaviorData = new BehaviorData();
	m_aiTree = behavior;
}

// CSV�t�@�C������f�[�^��ǂݍ���ŏ�����
void EnemyBehavior::Init(std::string fileName)
{
	BehaviorTree* behavior = new BehaviorTree();
	behavior = this->LoadDataFromCSV(behavior, fileName);

	m_behaviorData = new BehaviorData();
	m_aiTree = behavior;
}

// �f�[�^�̍폜
void EnemyBehavior::Uninit()
{
	delete m_aiTree;
	delete m_behaviorData;
}

// �m�[�h�̎��s
void EnemyBehavior::Upadate(Enemy* pEnemy)
{

	if (!m_activeNode)
	{
		m_activeNode = m_aiTree->Inference(pEnemy, m_behaviorData);
	}

	if (m_activeNode)
	{
		m_Timer += UPDATE_TIMER_AMOUNT;
		m_activeNode = m_aiTree->Run(pEnemy, m_activeNode, m_behaviorData, this);
	}
}

// ���݂̃m�[�h�̖��O���擾
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

// CSV�t�@�C������r�w�C�r�A�c���[�f�[�^��ǂݍ��݁A�m�[�h�ɒǉ�
BehaviorTree* EnemyBehavior::LoadDataFromCSV(BehaviorTree * pBehavior, std::string fileName)
{
	// �ǂݍ��ރf�[�^�\����
	AiData data;

	// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ifstream ifs_csv_file(fileName);
	
	//	�f�[�^����ǂݍ���
	int num;
	ifs_csv_file >> num;

	// �f�[�^�ǂݍ���
	for (int i = 0; i < num; i++)
	{
		ifs_csv_file >> data.ParentName;
		ifs_csv_file >> data.EntryName;
		ifs_csv_file >> data.Priority;
		ifs_csv_file >> data.SelectRule;
		ifs_csv_file >> data.JudgeNum;
		ifs_csv_file >> data.ActionNum;

		if (data.ParentName == "!")
		{
			data.ParentName = "";
		}

		BehaviorTree::SELECT_RULE selectRule = static_cast<BehaviorTree::SELECT_RULE>(data.SelectRule);

		ExecJudgmentBase* pJudgment;
		switch (data.JudgeNum)
		{
		default:
			pJudgment = nullptr;
			break;
		}

		ActionBase* pAction;
		switch (data.ActionNum)
		{
		case Behavior_Idle:
			pAction = EnemyBehaviorIdle::GetInstance();
			break;
		case Behavior_LookingFor:
			pAction = EnemyBehaviorLookingFor::GetInstance();
			break;
		case Behavior_Run:
			pAction = EnemyBehaviorRun::GetInstance();
			break;
		default:
			pAction = nullptr;
			break;
		}

		pBehavior->AddNode(data.ParentName, data.EntryName, data.Priority, selectRule, pJudgment, pAction);
	}
	return pBehavior;
}

