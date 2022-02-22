#pragma once

#include <vector>
#include <string>
#include "behaviorTree.h"
#include "actionBase.h"

class ExecJudgmentBase;
class BehaviorData;

// �m�[�h�C���^�[�t�F�[�X
class NodeBase
{
private:
	NodeBase() = delete;
public:
	NodeBase(std::string name, NodeBase* parent, NodeBase* sibling, unsigned int priority, BehaviorTree::SELECT_RULE selectRule, ExecJudgmentBase* execJudgment, ActionBase* action, int hierarchyNum):
		m_Name(name),
		m_Parent(parent),
		m_Sibling(sibling),
		m_Priority(priority),
		m_SelectRule(selectRule),
		m_ExecJudgment(execJudgment),
		m_Action(action),
		m_HierarchyNum(hierarchyNum),
		m_Child(NULL)
	{
	}

	//	���O�Q�b�^�[
	std::string GetName() { return m_Name; }

	//	�e�m�[�h�Q�b�^�[
	NodeBase* GetParent() { return m_Parent; }

	//	�q�m�[�h�Q�b�^�[(�I��)
	NodeBase* GetChiled(unsigned int index)
	{
		if (m_Child.size() >= index)
		{
			return nullptr;
		}
		return m_Child[index];
	}

	//	�q�m�[�h�Q�b�^�[(����)
	NodeBase* GetLastChiled()
	{
		if (m_Child.size() == 0)
		{
			return nullptr;
		}
	//	return *m_Child.end();
		return m_Child[m_Child.size()-1];
	}

	//	�q�m�[�h�Q�b�^�[(�擪)
	NodeBase* GetToptChiled()
	{
		if (m_Child.size() == 0)
		{
			return nullptr;
		}
		//	return *m_Child.begin();
		return m_Child[0];
	}

	//	�Z��m�[�h�Q�b�^�[
	NodeBase* GetSibling() { return m_Sibling; }

	//	�K�w�ԍ��Q�b�^�[
	int GetHierarchNum() { return m_HierarchyNum; }

	//	�D�揇�ʃQ�b�^�[
	int GetPriority() { return m_Priority; }

	//	�e�m�[�h�Z�b�^�[
	void Setparent(NodeBase* parent) { m_Parent = parent; }

	//	�q�m�[�h�ǉ�
	void AddChiled(NodeBase* child) { m_Child.push_back(child); }
	
	//	�Z��m�[�h�Z�b�^�[
	void SetSibling(NodeBase* sibling) { m_Sibling = sibling; }
	
	//	�s���f�[�^�̏���
	bool HaveAction() { return (m_Action != nullptr); }
	
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

	// ���s
	ActionBase::EXE_STATE Run(Enemy *pEnemy, class EnemyBehavior* pBehavior);
protected:
	std::string m_Name;						//	���O
	BehaviorTree::SELECT_RULE m_SelectRule;	//	�I�����[��
	ExecJudgmentBase *m_ExecJudgment;		//	����N���X
	ActionBase* m_Action;					//	���s�N���X
	unsigned int m_Priority;				//	�D�揇��
	NodeBase* m_Parent;						//	�e�m�[�h
	std::vector<NodeBase*> m_Child;			//	�q�m�[�h
	NodeBase* m_Sibling;					//	�Z��m�[�h
	int m_HierarchyNum;						//	�K�w�ԍ�
};