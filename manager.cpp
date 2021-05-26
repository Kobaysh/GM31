#include "main.h"
#include "manager.h"
#include "gameObject.h"
#include "Renderer.h"
#include "polygon2D.h"
#include "Camera.h"
#include "Field.h"
#include "model.h"
#include "Player.h"

// Ã“I•Ï”éŒ¾
//Manager* Manager::instance;
//Polygon2D* g_polygon = NULL;
//Camera* g_Camera = NULL;
//Field* g_Field = NULL;
//Player* g_Player = NULL;

enum GAMEOBJECT_TYPE
{
	CAMERA,
	POLYGON,
	FIELD,
	PLAYER,
	MAX,
};
//GameObject* g_polygon = NULL;
//GameObject* g_Camera = NULL;
//GameObject* g_Field = NULL;
//GameObject* g_Player = NULL;

GameObject* g_pGameObject[GAMEOBJECT_TYPE::MAX] = {};
//
//void Manager::Init()
//{
//	Renderer::Init();
//	g_polygon = new Polygon2D();
//	g_polygon->Init();
//}
//
//
//void Manager::Uninit()
//{
//
//	g_polygon->Uninit();
//	delete g_polygon;
//	Renderer::Uninit();
//}
//
//void Manager::Update()
//{
//	g_polygon->Update();
//}
//
//void Manager::Draw()
//{
//	Renderer::Begin();
//
//	g_polygon->Draw();
//
//
//	Renderer::End();
//}

void ManagerT::Init()
{
	Renderer::Init();
	/*g_polygon = new Polygon2D();
	g_polygon->Init();
	g_Camera = new Camera();
	g_Camera->Init();
	g_Field = new Field();
	g_Field->Init();
	g_Player = new Player();
	g_Player->Init();*/
	g_pGameObject[POLYGON] = new Polygon2D();
	g_pGameObject[POLYGON]->Init();
	g_pGameObject[CAMERA] = new Camera();
	g_pGameObject[CAMERA]->Init();
	g_pGameObject[FIELD] = new Field();
	g_pGameObject[FIELD]->Init();
	g_pGameObject[PLAYER] = new Player();
	g_pGameObject[PLAYER]->Init();
}

void ManagerT::Uninit()
{
	for (int i = 0; i < GAMEOBJECT_TYPE::MAX; i++) {
		g_pGameObject[i]->Uninit();
		delete g_pGameObject[i];
	}
	Renderer::Uninit();
}

void ManagerT::Update()
{
	/*g_Camera->Update();
	g_Field->Update();
	g_polygon->Update();
	g_Player->Update();*/

	for (int i = 0; i < GAMEOBJECT_TYPE::MAX; i++) {
		g_pGameObject[i]->Update();
	}

}

void ManagerT::Draw()
{
	Renderer::Begin();
	/*g_Camera->Draw();
	g_Field->Draw();
	g_Player->Draw();
	g_polygon->Draw();*/
	for (int i = 0; i < GAMEOBJECT_TYPE::MAX; i++) {
		g_pGameObject[i]->Draw();
	}

	Renderer::End();
}
