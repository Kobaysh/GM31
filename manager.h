#pragma once
#include "singleton.h"
#include "scene.h"
//class GameObject;


//
//class Manager : public Singleton
//{
//private:
//	Manager() = default;
//	~Manager() = default;
//
//	static Manager* instance;
//
//public:
//	Manager(const Manager&) = delete;
//	Manager& operator=(const Manager&) = delete;
//	Manager(Manager&&) = delete;
//	Manager& operator=(Manager&&) = delete;
//
//	static Manager& GetInstance() {
//		return *instance;
//	}
//
//	static void create() {
//		if (!instance) {
//			instance = new Manager;
//		}
//	}
//
//	static void Destroy() {
//		delete instance;
//		instance = NULL;
//	}
//
//
//	static void Init();
//	static void Uninit();
//	static void Update();
//	static void Draw();
//
//};

class ManagerT : public SingletonT<ManagerT>
{
private:
	friend class SingletonT<ManagerT>;
	static class Scene* m_Scene;

public:


	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static GameObject* AddGameObjectFromManager(GameObject* pObj) {
		return m_Scene->AddGameObject(pObj);
	}
	/*static void AddGameObjectFromManager(GameObject* pObj) 
	{
		m_Scene->AddGameObject(pObj);
	}*/
};