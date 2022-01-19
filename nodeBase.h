#pragma once

#include <vector>
#include <string>
#include "behaviorTree.h"
#include "actionBase.h"

class ExecJudgmentBase;
class BehaviorData;

class NodeBase
{
private:
	NodeBase() = delete;
public:
	NodeBase(std::string name, NodeBase* parent, NodeBase* sibling, unsigned int priority, BehabiorTree::SELECT_RULE selectRule, ExecJudgmentBase* execJudgment, ActionBase* action, int hierarchyNum):
		m_name(name),
		m_parent(parent),
		m_sibling(sibling),
		m_priority(priority),
		m_selectRule(selectRule),
		m_execJudgment(execJudgment),
		m_action(action),
		m_hierarchyNum(hierarchyNum),
		m_child(NULL)
	{
	}

	//	���O�Q�b�^�[
	std::string GetName() { return m_name; }

	//	�e�m�[�h�Q�b�^�[
	NodeBase* GetParent() { return m_parent; }

	//	�q�m�[�h�Q�b�^�[(�I��)
	NodeBase* GetChiled(unsigned int index)
	{
		if (m_child.size() >= index)
		{
			return nullptr;
		}
		return m_child[index];
	}

	//	�q�m�[�h�Q�b�^�[(����)
	NodeBase* GetLastChiled()
	{
		if (m_child.size() == 0)
		{
			return nullptr;
		}
	//	return *m_child.end();
		return m_child[m_child.size()-1];
	}

	//	�q�m�[�h�Q�b�^�[(�擪)
	NodeBase* GetToptChiled()
	{
		if (m_child.size() == 0)
		{
			return nullptr;
		}
		//	return *m_child.begin();
		return m_child[0];
	}

	//	�Z��m�[�h�Q�b�^�[
	NodeBase* GetSibling() { return m_sibling; }

	//	�K�w�ԍ��Q�b�^�[
	int GetHierarchNum() { return m_hierarchyNum; }

	//	�D�揇�ʃQ�b�^�[
	int GetPriority() { return m_priority; }

	//	�e�m�[�h�Z�b�^�[
	void Setparent(NodeBase* parent) { m_parent = parent; }

	//	�q�m�[�h�ǉ�
	void AddChiled(NodeBase* child) { m_child.push_back(child); }
	
	//	�Z��m�[�h�Z�b�^�[
	void SetSibling(NodeBase* sibling) { m_sibling = sibling; }
	
	//	�s���f�[�^�̏���
	bool HaveAction() { return (m_action != nullptr); }
	
	//	���s�۔���
	bool Judgment(Enemy* pEnemy);

	//	�D�揇�ʑI��
	NodeBase* SelectPriority(std::vector<NodeBase*> *list);
	// �����_���I��
	NodeBase* SelectRandom(std::vector<NodeBase*> *list);
	// �I���E�I�t�I��
	NodeBase *SelectOnOff(std::vector<NodeBase*> *list, BehaviorData *data);
	// �V�[�P���X�I��
	NodeBase *SelectSequence(std::vector<NodeBase*> *list, BehaviorData *data);

	// �m�[�h����
	NodeBase* SearchNode(std::string searchName);
	
	// �m�[�h���_
	NodeBase *Inference(Enemy* pEnemy, BehaviorData *data);

	// �m�[�h���\��
//	void PrintName();

	// ���s
	ActionBase::EXE_STATE Run(Enemy *pEnemy);
protected:
	std::string m_name;						//	���O
	BehabiorTree::SELECT_RULE m_selectRule;	//	�I�����[��
	ExecJudgmentBase *m_execJudgment;		//	����N���X
	ActionBase* m_action;					//	���s�N���X
	unsigned int m_priority;				//	�D�揇��
	NodeBase* m_parent;						//	�e�m�[�h
	std::vector<NodeBase*> m_child;			//	�q�m�[�h
	NodeBase* m_sibling;					//	�Z��m�[�h
	int m_hierarchyNum;						//	�K�w�ԍ�
};