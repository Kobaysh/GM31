#pragma once
#include <string>

class ActionBase;
class ExecJudgmentBase;
class NodeBase;
class Enemy;

class BehabiorTree
{
public:
	//	�I�����[��
	enum SELECT_RULE
	{
		NON,
		PRIORITY,		//	�D�揇��
		SEQUENCE,		//	�V�[�P���X
		SEQENTIAL_LOOP,	//	�V�[�P���V�������[�v
		RANDOM,			//	�����_��
		ON_OFF,			//	�I���E�I�t
	};
public:
	BehabiorTree() :
		m_root(nullptr)
	{
	}
	//	���s�m�[�h�𐄘_
//	NodeBase* Inference(Enemy* pEnemy, BehavaiorData* data);

// �V�[�P���X�m�[�h���琄�_�J�n
//	NodeBase *SequenceBack(NodeBase *sequence_node, Enemy *enemy, BehaviorData *data);

	// �m�[�h�ǉ�
	void AddNode(std::string searchName, std::string entryName, int priority, SELECT_RULE selectRule, ExecJudgmentBase* judgment, ActionBase* action);

	// �c���[�\����\��
//	void PrintTree();

	// ���s
//	NodeBase *Run(Enemy *enemy, NodeBase *action_node, BehaviorData *data);

private:
	//	���[�g�m�[�h
	NodeBase* m_root;
};