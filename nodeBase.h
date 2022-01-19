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

	//	名前ゲッター
	std::string GetName() { return m_name; }

	//	親ノードゲッター
	NodeBase* GetParent() { return m_parent; }

	//	子ノードゲッター(選択)
	NodeBase* GetChiled(unsigned int index)
	{
		if (m_child.size() >= index)
		{
			return nullptr;
		}
		return m_child[index];
	}

	//	子ノードゲッター(末尾)
	NodeBase* GetLastChiled()
	{
		if (m_child.size() == 0)
		{
			return nullptr;
		}
	//	return *m_child.end();
		return m_child[m_child.size()-1];
	}

	//	子ノードゲッター(先頭)
	NodeBase* GetToptChiled()
	{
		if (m_child.size() == 0)
		{
			return nullptr;
		}
		//	return *m_child.begin();
		return m_child[0];
	}

	//	兄弟ノードゲッター
	NodeBase* GetSibling() { return m_sibling; }

	//	階層番号ゲッター
	int GetHierarchNum() { return m_hierarchyNum; }

	//	優先順位ゲッター
	int GetPriority() { return m_priority; }

	//	親ノードセッター
	void Setparent(NodeBase* parent) { m_parent = parent; }

	//	子ノード追加
	void AddChiled(NodeBase* child) { m_child.push_back(child); }
	
	//	兄弟ノードセッター
	void SetSibling(NodeBase* sibling) { m_sibling = sibling; }
	
	//	行動データの所持
	bool HaveAction() { return (m_action != nullptr); }
	
	//	実行可否判定
	bool Judgment(Enemy* pEnemy);

	//	優先順位選択
	NodeBase* SelectPriority(std::vector<NodeBase*> *list);
	// ランダム選択
	NodeBase* SelectRandom(std::vector<NodeBase*> *list);
	// オン・オフ選択
	NodeBase *SelectOnOff(std::vector<NodeBase*> *list, BehaviorData *data);
	// シーケンス選択
	NodeBase *SelectSequence(std::vector<NodeBase*> *list, BehaviorData *data);

	// ノード検索
	NodeBase* SearchNode(std::string searchName);
	
	// ノード推論
	NodeBase *Inference(Enemy* pEnemy, BehaviorData *data);

	// ノード名表示
//	void PrintName();

	// 実行
	ActionBase::EXE_STATE Run(Enemy *pEnemy);
protected:
	std::string m_name;						//	名前
	BehabiorTree::SELECT_RULE m_selectRule;	//	選択ルール
	ExecJudgmentBase *m_execJudgment;		//	判定クラス
	ActionBase* m_action;					//	実行クラス
	unsigned int m_priority;				//	優先順位
	NodeBase* m_parent;						//	親ノード
	std::vector<NodeBase*> m_child;			//	子ノード
	NodeBase* m_sibling;					//	兄弟ノード
	int m_hierarchyNum;						//	階層番号
};