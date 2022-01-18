#include "execJudgmentBase.h"
#include "nodeBase.h"
#include "behaviorData.h"
#include "enemy.h"
#include "actionBase.h"

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
		data->ResetNodeUsed(&m_child);
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
	if (step >= m_child.size())
	{
		if (m_selectRule != BehabiorTree::SELECT_RULE::SEQENTIAL_LOOP)
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
		if (m_child[step]->GetName() == node->GetName())
		{
			// シーケンスノードを記録
			data->PushSequenceNode(this);
			// シーケンスステップを更新
			data->SetSequenceStep(this->GetName(), step + 1);
			return m_child[step];
		}
	}

	return nullptr;
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

NodeBase * NodeBase::Inference(Enemy * pEnemy, BehaviorData * data)
{
	std::vector<NodeBase*> list;
	NodeBase* result = nullptr;

	//	子ノードで実行可能なノードを探す
	for (int i = 0; i < m_child.size(); i++)
	{
		if (m_child[i]->m_execJudgment)
		{

			if (m_child[i]->m_execJudgment->Judgment(pEnemy))
			{
				list.push_back(m_child[i]);
			}
		}
		else
		{
			// 判定クラスがなければ無条件に追加
			list.push_back(m_child[i]);
		}
	}
	// 選択ルールでノード決め
	switch (m_selectRule)
	{
	case BehabiorTree::NON:
		break;
	
	// 優先順位
	case BehabiorTree::PRIORITY:
		result = SelectPriority(&list);
		break;
	case BehabiorTree::SEQUENCE:
	case BehabiorTree::SEQENTIAL_LOOP:
		result = SelectSequence(&list, data);
		break;
	case BehabiorTree::RANDOM:
		result = SelectRandom(&list);
		break;
	case BehabiorTree::ON_OFF:
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

ActionBase::EXE_STATE NodeBase::Run(Enemy * pEnemy)
{
	// アクションノードが存在してるなら結果を、なければ失敗を返す
	if (m_action)
	{
		return m_action->Run(pEnemy);
	}

	return ActionBase::FAILED;
}
