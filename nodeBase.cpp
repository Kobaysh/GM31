#include "execJudgmentBase.h"
#include "nodeBase.h"

bool NodeBase::Judgment(Enemy * pEnemy)
{
	//	����N���X�������Ă���Ύ��s�A�Ȃ����true
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

	//  �D�揇�ʂ���ԍ����m�[�h��T��
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
	// �A�N�V�����m�[�h�����݂��Ă�Ȃ猋�ʂ��A�Ȃ���Ύ��s��Ԃ�
	if (m_action)
	{
		return m_action->Run(pEnemy);
	}

	return ActionBase::FAILED;
}
