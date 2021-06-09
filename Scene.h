#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "gameObject.h"
#include "polygon2D.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"


class Scene
{
public:
	Scene(){}
	virtual ~Scene(){}

	template <typename TS>
	TS* AppendGameObject() {
		TS* gameObject = new TS();
		gameObject->Init();
		m_GameObject.push_back(gameObject);
		return gameObject;
	}
	GameObject* AddGameObject(GameObject* pObj) {
		if (pObj == nullptr)return nullptr;
		pObj->Init();
		m_GameObject.push_back(pObj);
		return pObj;
	}

	template<typename TS>
	TS* GetGameObject() {
		for (GameObject*object : m_GameObject) {
			if (typeid(*object) == typeid(TS)) {	// 型を調べる(RTTI動的型情報)
				return (TS*)object;
			}
		}
		return nullptr;
	}

	template<typename TS>
	std::vector<TS*> GetGameObjects() {
		std::vector<TS*> objects;
		for (GameObject* object : m_GameObject) {
			if (typeid(*object) == typeid(TS)) {
				objects.push_back((TS*)object);
			}
		}
		return objects;
	}

protected:
	std::list<GameObject*> m_GameObject;	// STLのリスト構造
public:
	virtual void Init() {
		/*AppendGameObject<Camera>();
		AppendGameObject<Field>();
		AppendGameObject<Player>();
		AppendGameObject<Polygon2D>();
		AppendGameObject<Enemy>();*/

		/*Polygon2D* polygon2D = new Polygon2D();
		AddGameObject(polygon2D);*/
		Camera* camera = new Camera();
		AddGameObject(camera);
		
		Field* field = new Field();
		AddGameObject(field);
		Player* player = new Player();
		AddGameObject(player);
		player->SetPosition(XMFLOAT3(0.0f, 1.0f, -4.0f));
		Enemy* enemy = new Enemy();
		AddGameObject(enemy)->SetPosition(XMFLOAT3(5.0f, 1.0f, 1.0f));
		Enemy* enemy02 = new Enemy();
		AddGameObject(enemy02)->SetPosition(XMFLOAT3(0.0f, 1.0f, 1.0f));
		Enemy* enemy03 = new Enemy();
		AddGameObject(enemy03)->SetPosition(XMFLOAT3(-5.0f, 1.0f, 1.0f));
		
	}
	virtual void Uninit() {
		for (GameObject* object : m_GameObject) {
			object->Uninit();
			delete object;
		}
		m_GameObject.clear();	// リストのクリア
	}
	virtual void Update() {
		for (GameObject* object : m_GameObject) {
			object->Update();
		}
		// forloopの外でないとダメ
		m_GameObject.remove_if(
			[](GameObject* object) {
				return object->Destroy(); 
			}
		);
		// ラムダ式	
	}
	virtual void Draw() {
		for (GameObject* object : m_GameObject) {
			object->Draw();
		}
	}
};

