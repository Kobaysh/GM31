#include "execJudgmentBase.h"
#include "nodeBase.h"
#include "behaviorData.h"
#include "enemy.h"
#include "actionBase.h"

bool NodeBase::Judgment(Enemy * pEnemy)
{
	//	判定クラスを持っていれば実行、なければtrue
	if (m_ExecJudgment)
	{
		return m_ExecJudgment->Judgment(pEnemy);
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

NodeBase * NodeBase::SelectOnOff(std::vector<NodeBase*>* list, BehaviorData * data)
{
	std::vector<NodeBase*> offList;

	// 使用済みノードをリストアップ
	for (NodeBase* node : *list)
	{
		if (!data->IsNodeUsed(node->GetName()))
		{
			offList.push_back(node);
		}
	}

	// リストアップした数をチェック
	if (offList.size() == 0)
	{
		// ノードをリセット
		data->ResetNodeUsed(&m_Child);
		offList = *list;
	}

	// 使用ノードを登録
	data->EntryUsedNode(offList[0]->GetName());

	// リストの先頭が決定したノード
	return offList[0];
}

NodeBase * NodeBase::SelectSequence(std::vector<NodeBase*>* list, BehaviorData * data)
{
	// 今のノードのシーケンスのステップを取得
	int step = data->GetSequenceStep(this->GetName());

	// シーケンスが終わってたら終了
	if (step >= m_Child.size())
	{
		if (m_SelectRule != BehaviorTree::SELECT_RULE::SEQENTIAL_LOOP)
		{
			return nullptr;
		}
		else
		{
			// Loopの場合は先頭から実行
			step = 0;
		}
	}

	// 順番のノードが実行できるかのチェック
	for (NodeBase* node : *list)
	{
		if (m_Child[step]->GetName() == node->GetName())
		{
			// シーケンスノードを記録
			data->PushSequenceNode(this);
			// シーケンスステップを更新
			data->SetSequenceStep(this->GetName(), step + 1);
			return m_Child[step];
		}
	}

	return nullptr;
}

NodeBase * NodeBase::SearchNode(std::string searchName)
{
	if (m_Name == searchName)
	{
		return this;
	}
	else
	{
		for (auto child : m_Child)
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

NodeBase * NodeBase::Inference(Enemy * pEnemy, BehaviorData * data)
{
	std::vector<NodeBase*> list;
	NodeBase* result = nullptr;

	//	子ノードで実行可能なノードを探す
	for (int i = 0; i < m_Child.size(); i++)
	{
		if (m_Child[i]->m_ExecJudgment)
		{

			if (m_Child[i]->m_ExecJudgment->Judgment(pEnemy))
			{
				list.push_back(m_Child[i]);
			}
		}
		else
		{
			// 判定クラスがなければ無条件に追加
			list.push_back(m_Child[i]);
		}
	}
	// 選択ルールでノード決め
	switch (m_SelectRule)
	{
	case BehaviorTree::NON:
		break;
	
	// 優先順位
	case BehaviorTree::PRIORITY:
		result = SelectPriority(&list);
		break;
	case BehaviorTree::SEQUENCE:
	case BehaviorTree::SEQENTIAL_LOOP:
		result = SelectSequence(&list, data);
		break;
	case BehaviorTree::RANDOM:
		result = SelectRandom(&list);
		break;
	case BehaviorTree::ON_OFF:
		result = SelectOnOff(&list, data);
		break;
	default:
		break;
	}

	if (result)
	{
		// 行動があれば終了
		if (result->HaveAction())
		{
			return result;
		}
		else
		{
			// 決まったノードで推論開始
			result = result->Inference(pEnemy, data);
		}
	}


	return result;
}

ActionBase::EXE_STATE NodeBase::Run(Enemy * pEnemy, class EnemyBehavior* pBehavior)
{
	// アクションノードが存在してるなら結果を、なければ失敗を返す
	if (m_Action)
	{
		return m_Action->Run(pEnemy, pBehavior);
	}

	return ActionBase::FAILED;
}
