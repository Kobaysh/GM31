#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "keylogger.h"
#include "audio.h"
#include "manager.h"

Scene* ManagerT::m_Scene = nullptr;

void ManagerT::Init()
{

	KeyLogger_Init();
	Renderer::Init();
	Audio::InitMaster();


	SetScene<Title>();
//	SetScene<Game>();
//	SetScene<Result>();

	
}

void ManagerT::Uninit()
{
	if (m_Scene) {
		m_Scene->Uninit();
		delete m_Scene;
	}
	Audio::UninitMaster();
	Renderer::Uninit();
	KeyLogger_Fin();
}

void ManagerT::Update()
{
	KeyLogger_Update();
	if (m_Scene) {
		m_Scene->Update();
	}
}

void ManagerT::Draw()
{
	Renderer::Begin();
	if (m_Scene) {
		m_Scene->Draw();
	}
	Renderer::End();
}

