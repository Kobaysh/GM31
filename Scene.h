#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "gameObject.h"

// シーンインターフェース
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[GameObject::GOT_MAX];	// STLのリスト構造
	bool m_IsFading;											// フェード中かどうか
public:
	Scene(){}
	virtual ~Scene(){}

	// ゲームオブジェクト管理下に追加
	template <typename TS>
	TS* AppendGameObject(GameObject::GameObject_Type type) {
		TS* gameObject = new TS();
		gameObject->Init();
		m_GameObject[type].push_back(gameObject);
		return gameObject;
	}
	template<typename T>
	T* AddGameObject(T* pObj, GameObject::GameObject_Type type) {
		if (pObj == nullptr)return nullptr;
		pObj->Init();
		m_GameObject[type].push_back(pObj);
		return pObj;
	}
	GameObject* AddGameObject(GameObject* pObj, GameObject::GameObject_Type type) {
		if (pObj == nullptr)return nullptr;
		pObj->Init();
		m_GameObject[type].push_back(pObj);
		return pObj;
	}

	// ゲームオブジェクトインスタンスゲッター
	template<typename TS>
	TS* GetGameObject(GameObject::GameObject_Type type) {

		for (GameObject*object : m_GameObject[type]) {
			if (typeid(*object) == typeid(TS)) {	// 型を調べる(RTTI動的型情報)
				return (TS*)object;
			}
		}

		return nullptr;
	}

	template<typename TS>
	std::vector<TS*> GetGameObjects(GameObject::GameObject_Type type) {
		std::vector<TS*> objects;
			for (GameObject* object : m_GameObject[type]) {
				if (typeid(*object) == typeid(TS)) {
					objects.push_back((TS*)object);
				}
			}
		return objects;
	}

	// 初期化
	virtual void Init() = 0;

	// 終了処理
	virtual void Uninit() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();	// リストのクリア
		}
	}

	// 更新処理
	virtual void Update() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Update();
			}
			// forroopの外でないとダメ
			m_GameObject[i].remove_if(
				[](GameObject* object) {
					return object->Destroy();
				}
			);
			// ラムダ式	
		}
	}
	// 描画処理
	virtual void Draw() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}
};

