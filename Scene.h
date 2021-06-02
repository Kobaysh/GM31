#pragma once
#include <list>
#include "gameObject.h"
#include "polygon2D.h"
#include "Camera.h"
#include "Field.h"
#include "model.h"
#include "Player.h"


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
protected:
	std::list<GameObject*> m_GameObject;	// STLのリスト構造
public:
	virtual void Init() {
		AppendGameObject<Camera>();
		AppendGameObject<Field>();
		AppendGameObject<Player>();
		AppendGameObject<Polygon2D>();
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
	}
	virtual void Draw() {
		for (GameObject* object : m_GameObject) {
			object->Draw();
		}
	}
};

