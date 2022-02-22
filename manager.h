#pragma once
#include "singleton.h"

// �A�v���Ǘ��N���X
class ManagerT : public SingletonT<ManagerT>
{
private:
	friend class SingletonT<ManagerT>;	// �V���O���g���p
	static class Scene* m_Scene;		// �V�[���I�u�W�F�N�g

public:


	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// �V�[���Z�b�g
	template<typename T>
	static void SetScene() {
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}
		m_Scene = new T();
		m_Scene->Init();
	}

	/*static GameObject* AddGameObjectFromManager(GameObject* pObj) {
		return m_Scene->AddGameObject(pObj);
	}*/
	/*static void AddGameObjectFromManager(GameObject* pObj) 
	{
		m_Scene->AddGameObject(pObj);
	}*/

	// �V�[���C���X�^���X�Q�b�^�[
	static class Scene* GetScene() { return m_Scene; }
};
