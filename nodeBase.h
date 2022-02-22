#pragma once

#include <vector>
#include <string>
#include "behaviorTree.h"
#include "actionBase.h"

class ExecJudgmentBase;
class BehaviorData;

// ノードインターフェース
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

	//	名前ゲッター
	std::string GetName() { return m_Name; }

	//	親ノードゲッター
	NodeBase* GetParent() { return m_Parent; }

	//	子ノードゲッター(選択)
	NodeBase* GetChiled(unsigned int index)
	{
		if (m_Child.size() >= index)
		{
			return nullptr;
		}
		return m_Child[index];
	}

	//	子ノードゲッター(末尾)
	NodeBase* GetLastChiled()
	{
		if (m_Child.size() == 0)
		{
			return nullptr;
		}
	//	return *m_Child.end();
		return m_Child[m_Child.size()-1];
	}

	//	子ノードゲッター(先頭)
	NodeBase* GetToptChiled()
	{
		if (m_Child.size() == 0)
		{
			return nullptr;
		}
		//	return *m_Child.begin();
		return m_Child[0];
	}

	//	兄弟ノードゲッター
	NodeBase* GetSibling() { return m_Sibling; }

	//	階層番号ゲッター
	int GetHierarchNum() { return m_HierarchyNum; }

	//	優先順位ゲッター
	int GetPriority() { return m_Priority; }

	//	親ノードセッター
	void Setparent(NodeBase* parent) { m_Parent = parent; }

	//	子ノード追加
	void AddChiled(NodeBase* child) { m_Child.push_back(child); }
	
	//	兄弟ノードセッター
	void SetSibling(NodeBase* sibling) { m_Sibling = sibling; }
	
	//	行動データの所持
	bool HaveAction() { return (m_Action != nullptr); }
	
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

	// 実行
	ActionBase::EXE_STATE Run(Enemy *pEnemy, class EnemyBehavior* pBehavior);
protected:
	std::string m_Name;						//	名前
	BehaviorTree::SELECT_RULE m_SelectRule;	//	選択ルール
	ExecJudgmentBase *m_ExecJudgment;		//	判定クラス
	ActionBase* m_Action;					//	実行クラス
	unsigned int m_Priority;				//	優先順位
	NodeBase* m_Parent;						//	親ノード
	std::vector<NodeBase*> m_Child;			//	子ノード
	NodeBase* m_Sibling;					//	兄弟ノード
	int m_HierarchyNum;						//	階層番号
};