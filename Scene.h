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
protected:
	std::list<GameObject*> m_GameObject;	// STLのリスト構造
public:
	virtual void Init() {
		Camera* camera = new Camera();
		camera->Init();
		m_GameObject.push_back(camera);

		Field* field = new Field();
		field->Init();
		m_GameObject.push_back(field);

		Player* player = new Player();
		player->Init();
		m_GameObject.push_back(player);

		Polygon2D* polygon2D = new Polygon2D();
		polygon2D->Init();
		m_GameObject.push_back(polygon2D);
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

