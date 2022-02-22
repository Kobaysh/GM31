#pragma once
#include <string>
#include "state.h"

class Enemy;

// �X�e�[�g�p�^�[���C���^�[�t�F�[�X
class EnemyStatePattern
{
public:
	virtual ~EnemyStatePattern(){}
	virtual void Update(class Enemy* pEnemy) = 0;
};

// �GAI�X�e�[�g�}�V�[���N���X
class EnemyState
{
public:
	EnemyState();
	~EnemyState();
	void Update(Enemy* pEnemy);

	// �X�e�[�g�ؑ�
	EnemyStatePattern* ChangeState(EnemyStatePattern* pStatePattern);

	// �K�[�h���Z�b�^�[
	void SetIsGuarding(bool isGuarding) { m_IsGuarding = isGuarding; }

	// �K�[�h���Q�b�^�[
	bool GetIsGuarding() const { return m_IsGuarding; }

	// �_���[�W���Z�b�^�[
	void SetIsDamaged(bool isDamaged) { m_IsDamaged = isDamaged; }

	// �_���[�W���Q�b�^�[
	bool GetIsDamaged() const { return m_IsDamaged; }

	// �q�b�g�Z�b�^�[
	void SetIsCollided(bool isCollided) { m_IsCollided = isCollided; }

	// �q�b�g�Q�b�^�[
	bool GetIsCollided() const { return m_IsCollided; }

	// �X�e�[�g���Z�b�^�[
	void SetStateName(std::string name) { m_StateName = name; }

	// �X�e�[�g���Q�b�^�[
	std::string& GetStateName() { return m_StateName; }
private:
	EnemyStatePattern* m_StatePattern;	// ���
	bool m_IsGuarding = false;			// �K�[�h����
	bool m_IsDamaged = false;			// ��_���[�W����
	bool m_IsCollided = false;			// �������Ă��邩
	std::string m_StateName;			// �X�e�[�g��
};
