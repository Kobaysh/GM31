#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "manager.h"
Scene* ManagerT::m_Scene;

void ManagerT::Init()
{
	Renderer::Init();
	m_Scene = new Game();
	m_Scene->Init();
}

void ManagerT::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;
	Renderer::Uninit();
}

void ManagerT::Update()
{
	m_Scene->Update();
}

void ManagerT::Draw()
{
	Renderer::Begin();
	
	m_Scene->Draw();

	Renderer::End();
}

