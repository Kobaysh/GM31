#include "execJudgmentBase.h"
#include "nodeBase.h"
#include "behaviorData.h"
#include "enemy.h"
#include "actionBase.h"

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

NodeBase * NodeBase::SelectOnOff(std::vector<NodeBase*>* list, BehaviorData * data)
{
	std::vector<NodeBase*> offList;

	// �g�p�ς݃m�[�h�����X�g�A�b�v
	for (NodeBase* node : *list)
	{
		if (!data->IsNodeUsed(node->GetName()))
		{
			offList.push_back(node);
		}
	}

	// ���X�g�A�b�v���������`�F�b�N
	if (offList.size() == 0)
	{
		// �m�[�h�����Z�b�g
		data->ResetNodeUsed(&m_child);
		offList = *list;
	}

	// �g�p�m�[�h��o�^
	data->EntryUsedNode(offList[0]->GetName());

	// ���X�g�̐擪�����肵���m�[�h
	return offList[0];
}

NodeBase * NodeBase::SelectSequence(std::vector<NodeBase*>* list, BehaviorData * data)
{
	// ���̃m�[�h�̃V�[�P���X�̃X�e�b�v���擾
	int step = data->GetSequenceStep(this->GetName());

	// �V�[�P���X���I����Ă���I��
	if (step >= m_child.size())
	{
		if (m_selectRule != BehabiorTree::SELECT_RULE::SEQENTIAL_LOOP)
		{
			return nullptr;
		}
		else
		{
			// Loop�̏ꍇ�͐擪������s
			step = 0;
		}
	}

	// ���Ԃ̃m�[�h�����s�ł��邩�̃`�F�b�N
	for (NodeBase* node : *list)
	{
		if (m_child[step]->GetName() == node->GetName())
		{
			// �V�[�P���X�m�[�h���L�^
			data->PushSequenceNode(this);
			// �V�[�P���X�X�e�b�v���X�V
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

	//	�q�m�[�h�Ŏ��s�\�ȃm�[�h��T��
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
			// ����N���X���Ȃ���Ζ������ɒǉ�
			list.push_back(m_child[i]);
		}
	}
	// �I�����[���Ńm�[�h����
	switch (m_selectRule)
	{
	case BehabiorTree::NON:
		break;
	
	// �D�揇��
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
		// �s��������ΏI��
		if (result->HaveAction())
		{
			return result;
		}
		else
		{
			// ���܂����m�[�h�Ő��_�J�n
			result = result->Inference(pEnemy, data);
		}
	}


	return result;
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
