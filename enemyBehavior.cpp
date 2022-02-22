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


const float EnemyBehavior::UPDATE_TIMER_AMOUNT = 0.01f;	// updateで増やすタイマーの量
const std::string EnemyBehavior::DATA_FILE_NAME;		// ファイル名

// アクション名前
enum ActionInstanceName
{
	Behavior_Idle,
	Behavior_LookingFor,
	Behavior_Run,
};

// 読み込むデータ
struct AiData
{
	std::string ParentName;	// 親ノード名
	std::string EntryName;	// 登録ノード名
	int Priority;			// 優先度
	int SelectRule;			// 選択ルール
	int JudgeNum;			// 判定数字
	int ActionNum;			// アクション数字
};

// 初期化
void EnemyBehavior::Init()
{
	BehaviorTree* behavior = new BehaviorTree();
	behavior->AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, nullptr, nullptr);
	behavior->AddNode("Root", "LookingForPlayer", 0, BehaviorTree::SELECT_RULE::SEQENTIAL_LOOP, nullptr, nullptr);
	behavior->AddNode("LookingForPlayer", "Idle", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorIdle::GetInstance());
	behavior->AddNode("LookingForPlayer", "Lookingfor", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorLookingFor::GetInstance());
	behavior->AddNode("LookingForPlayer", "Run", 0, BehaviorTree::SELECT_RULE::NON, nullptr, EnemyBehaviorRun::GetInstance());
//	behavior = this->LoadDataFromCSV(behavior, "asset\\csv\\test.csv");

	m_BehaviorData = new BehaviorData();
	m_AiTree = behavior;
}

// CSVファイルからデータを読み込んで初期化
void EnemyBehavior::Init(std::string fileName)
{
	BehaviorTree* behavior = new BehaviorTree();
	behavior = this->LoadDataFromCSV(behavior, fileName);

	m_BehaviorData = new BehaviorData();
	m_AiTree = behavior;
}

// データの削除
void EnemyBehavior::Uninit()
{
	delete m_AiTree;
	delete m_BehaviorData;
}

// ノードの実行
void EnemyBehavior::Upadate(Enemy* pEnemy)
{

	if (!m_ActiveNode)
	{
		m_ActiveNode = m_AiTree->Inference(pEnemy, m_BehaviorData);
	}

	if (m_ActiveNode)
	{
		m_Timer += UPDATE_TIMER_AMOUNT;
		m_ActiveNode = m_AiTree->Run(pEnemy, m_ActiveNode, m_BehaviorData, this);
	}
}

// 現在のノードの名前を取得
std::string EnemyBehavior::GetActiveNodeName()
{
	if (m_ActiveNode)
	{
		return	m_ActiveNode->GetName();
	} 
	else
	{
		return "Root";
	}
}

// CSVファイルからビヘイビアツリーデータを読み込み、ノードに追加
BehaviorTree* EnemyBehavior::LoadDataFromCSV(BehaviorTree * pBehavior, std::string fileName)
{
	// 読み込むデータ構造体
	AiData data;

	// 読み込むcsvファイルを開く(std::ifstreamのコンストラクタで開く)
	std::ifstream ifs_csv_file(fileName);
	
	//	データ数を読み込む
	int num;
	ifs_csv_file >> num;

	// データ読み込み
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

