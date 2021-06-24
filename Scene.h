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
#include "explosion.h"


class Scene
{
protected:
	std::list<GameObject*> m_GameObject[GameObject::GOT_MAX];	// STLのリスト構造

public:
	Scene(){}
	virtual ~Scene(){}

	template <typename TS>
	TS* AppendGameObject(GameObject::GameObject_Type type) {
		TS* gameObject = new TS();
		gameObject->Init();
		m_GameObject[type].push_back(gameObject);
		return gameObject;
	}
	GameObject* AddGameObject(GameObject* pObj, GameObject::GameObject_Type type) {
		if (pObj == nullptr)return nullptr;
		pObj->Init();
		m_GameObject[type].push_back(pObj);
		return pObj;
	}

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
	std::vector<TS*> GetGameObjects() {
		std::vector<TS*> objects;
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				if (typeid(*object) == typeid(TS)) {
					objects.push_back((TS*)object);
				}
			}
		}
		return objects;
	}

	virtual void Init() {
		Bullet::Load();
		AppendGameObject<Camera>(GameObject::GOT_CAMERA);
		AppendGameObject<Field>(GameObject::GOT_OBJECT3D);
		AppendGameObject<Player>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, -4.0f));
		AppendGameObject<Polygon2D>(GameObject::GOT_OBJECT2D);
		AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(5.0f, 1.0f, 1.0f));
		AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, 1.0f));
		AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(-5.0f, 1.0f, 1.0f));
		//Polygon2D* polygon2D = new Polygon2D();
		//AddGameObject(polygon2D, GameObject::GOT_OBJECT2D);
		//Camera* camera = new Camera();
		//AddGameObject(camera, GameObject::GOT_CAMERA);
		//
		//Field* field = new Field();
		//AddGameObject(field, GameObject::GOT_OBJECT3D);
		//Player* player = new Player();
		//AddGameObject(player, GameObject::GOT_OBJECT3D);
		//player->SetPosition(XMFLOAT3(0.0f, 1.0f, -4.0f));
		//Enemy* enemy = new Enemy();
		//AddGameObject(enemy, GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(5.0f, 1.0f, 1.0f));
		//Enemy* enemy02 = new Enemy();
		//AddGameObject(enemy02, GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, 1.0f));
		//Enemy* enemy03 = new Enemy();
		//AddGameObject(enemy03, GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(-5.0f, 1.0f, 1.0f));
		
	}
	virtual void Uninit() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();	// リストのクリア
		}
		Bullet::UnLoad();
		Model::Uninit();
	}
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
	virtual void Draw() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}

	virtual void AllPSChange(const char* pFileName) {
		for (int i = GameObject::GOT_OBJECT3D; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->SetPShader(pFileName);
			}
		}
	}
};

