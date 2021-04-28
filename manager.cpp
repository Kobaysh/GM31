#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"

// Ã“I•Ï”éŒ¾
Manager* Manager::instance;
Polygon2D* g_polygon;


void Manager::Init()
{
	Renderer::Init();
	g_polygon = new Polygon2D();
	g_polygon->Init();
}


void Manager::Uninit()
{

	g_polygon->Uninit();
	delete g_polygon;
	Renderer::Uninit();
}

void Manager::Update()
{
	g_polygon->Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_polygon->Draw();


	Renderer::End();
}

void ManagerT::Init()
{
	Renderer::Init();
	g_polygon = new Polygon2D();
	g_polygon->Init();
}

void ManagerT::Uninit()
{
	g_polygon->Uninit();
	delete g_polygon;
	Renderer::Uninit();
}

void ManagerT::Update()
{
	g_polygon->Update();
}

void ManagerT::Draw()
{
	Renderer::Begin();

	g_polygon->Draw();


	Renderer::End();
}
