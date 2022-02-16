#include "behaviorTree.h"
#include "nodeBase.h"
#include "actionBase.h"
#include "execJudgmentBase.h"
#include "enemy.h"
#include "behaviorData.h"

NodeBase* BehaviorTree::Inference(Enemy * pEnemy, BehaviorData * data)
{
	// �f�[�^�����Z�b�g���ĊJ�n
	data->Init();
	return m_root->Inference(pEnemy, data);
}

NodeBase* BehaviorTree::SequenceBack(NodeBase * sequenceNode, Enemy * pEnemy, BehaviorData * data)
{
	return sequenceNode->Inference(pEnemy, data);
}

void BehaviorTree::AddNode(std::string searchName, std::string entryName, int priority, SELECT_RULE selectRule, ExecJudgmentBase * judgment, ActionBase * action)
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

NodeBase* BehaviorTree::Run(Enemy * pEnemy, NodeBase * actionNode, BehaviorData * data)
{
	// �m�[�h���s
	ActionBase::EXE_STATE state = actionNode->Run(pEnemy);
	// ����I���Ȃ�
	if (state == ActionBase::EXE_STATE::COMPLETE)
	{
		// �V�[�P���X�̓r�������f
		NodeBase* sequenceNode = data->PopSequenceNode();

		// �r���Ȃ�p���A�Ȃ��Ȃ�I��
		if (sequenceNode)
		{
			return SequenceBack(sequenceNode, pEnemy, data);
		}
		else
		{
			return nullptr;
		}
	}
	// ���s�Ȃ�I��
	else if (state == ActionBase::EXE_STATE::FAILED)
	{
		return nullptr;
	}

	// ����ȊO�͌���ێ�
	return actionNode;
}
