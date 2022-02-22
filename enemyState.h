#pragma once
#include <string>
#include "state.h"

class Enemy;

// ステートパターンインターフェース
class EnemyStatePattern
{
public:
	virtual ~EnemyStatePattern(){}
	virtual void Update(class Enemy* pEnemy) = 0;
};

// 敵AIステートマシーンクラス
class EnemyState
{
public:
	EnemyState();
	~EnemyState();
	void Update(Enemy* pEnemy);

	// ステート切替
	EnemyStatePattern* ChangeState(EnemyStatePattern* pStatePattern);

	// ガード中セッター
	void SetIsGuarding(bool isGuarding) { m_IsGuarding = isGuarding; }

	// ガード中ゲッター
	bool GetIsGuarding() const { return m_IsGuarding; }

	// ダメージ中セッター
	void SetIsDamaged(bool isDamaged) { m_IsDamaged = isDamaged; }

	// ダメージ中ゲッター
	bool GetIsDamaged() const { return m_IsDamaged; }

	// ヒットセッター
	void SetIsCollided(bool isCollided) { m_IsCollided = isCollided; }

	// ヒットゲッター
	bool GetIsCollided() const { return m_IsCollided; }

	// ステート名セッター
	void SetStateName(std::string name) { m_StateName = name; }

	// ステート名ゲッター
	std::string& GetStateName() { return m_StateName; }
private:
	EnemyStatePattern* m_StatePattern;	// 状態
	bool m_IsGuarding = false;			// ガード中か
	bool m_IsDamaged = false;			// 被ダメージ中か
	bool m_IsCollided = false;			// 当たっているか
	std::string m_StateName;			// ステート名
};
