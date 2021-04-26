#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "polygon2D.h"

// �ÓI�ϐ��錾
Manager* Manager::instance;
Polygon2D g_polygon;

void Manager::Init()
{
	Renderer::Init();
	g_polygon.Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();
	g_polygon.Uninit();
}

void Manager::Update()
{
	g_polygon.Update();
}

void Manager::Draw()
{
	Renderer::Begin();

	g_polygon.Draw();


	Renderer::End();
}
