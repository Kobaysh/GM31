#pragma once
#include "singleton.h"

// アプリ管理クラス
class ManagerT : public SingletonT<ManagerT>
{
private:
	friend class SingletonT<ManagerT>;	// シングルトン用
	static class Scene* m_Scene;		// シーンオブジェクト

public:


	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	// シーンセット
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

	// シーンインスタンスゲッター
	static class Scene* GetScene() { return m_Scene; }
};
