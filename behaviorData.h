#pragma once
#include <vector>
#include <stack>
#include <map>
#include "behaviorTree.h"

class NodeBase;
class Enemy;

class BehaviorData
{
public:

	BehaviorData() { Init(); }

	// �V�[�P���X�m�[�h�̃v�b�V��
	void PushSequenceNode(NodeBase* node)
	{
		m_sequenceStack.push(node);
	}

	// �V�[�P���X�m�[�h�̃|�b�v
	NodeBase* PopSequenceNode()
	{
		if (m_sequenceStack.empty())
		{
			return nullptr;
		}

		NodeBase* node = m_sequenceStack.top();

		if (node)
		{
			m_sequenceStack.pop();
		}
		return node;
	}

	// �m�[�h�g�p����
	bool IsNodeUsed(std::string name)
	{
		if (m_usedNodeMap.count(name) == 0)
		{
			return false;
		}
		return m_usedNodeMap[name];
	}

	// �g�p�ς݃m�[�h�ɓo�^
	void EntryUsedNode(std::string	name)
	{
		m_usedNodeMap[name] = true;
	}

	// �V�[�P���X�X�e�b�v�̃Q�b�^�[
	int GetSequenceStep(std::string name)
	{
		if (m_runSequenceStepMap.count(name) == 0)
		{
			m_runSequenceStepMap[name] = 0;
		}
		return m_runSequenceStepMap[name];
	}

	// �V�[�P���X�X�e�b�v�̃Z�b�^�[
	void SetSequenceStep(std::string name, int step)
	{
		m_runSequenceStepMap[name] = step;
	}

	// ������
	void Init()
	{
		m_runSequenceStepMap.clear();
		while (m_sequenceStack.size() > 0)
		{
			m_sequenceStack.pop();
		}
	}

	// �g�p�ς݃m�[�h�̃��Z�b�g
	void ResetNodeUsed(std::vector<NodeBase*> *resetHierachy);

private:
	std::stack<NodeBase*> m_sequenceStack;				// �V�[�P���X�m�[�h�X�^�b�N
	std::map<std::string, int> m_runSequenceStepMap;	// ���s�V�[�P���X�̃X�e�b�v�}�b�v
	std::map<std::string, bool> m_usedNodeMap;			// �m�[�h�̎g�p����}�b�v
};