#include "main.h"
#include "manager.h"
#include "Renderer.h"
#include "polygon2D.h"
#include "Camera.h"
#include "Field.h"

// Ã“I•Ï”éŒ¾
//Manager* Manager::instance;
Polygon2D* g_polygon = NULL;
Camera* g_Camera = NULL;
Field* g_Field = NULL;
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
	g_polygon = new Polygon2D();
	g_polygon->Init();
	g_Camera = new Camera();
	g_Camera->Init();
	g_Field = new Field();
	g_Field->Init();


	
}

void ManagerT::Uninit()
{
	g_polygon->Uninit();
	delete g_polygon;
	g_Camera->Uninit();
	delete g_Camera;
	g_Field->Uninit();
	delete g_Field;

	Renderer::Uninit();
}

void ManagerT::Update()
{
	g_Camera->Update();
	g_Field->Update();
	g_polygon->Update();
}

void ManagerT::Draw()
{
	Renderer::Begin();
//	g_Camera->Draw();
//	g_Field->Draw();
	g_polygon->Draw();
	Renderer::End();
}
