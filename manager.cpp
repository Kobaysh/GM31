#include "main.h"
#include "manager.h"
#include "renderer.h"

// �ÓI�ϐ��錾
Manager* Manager::instance;

void Manager::Init()
{
	Renderer::Init();
}


void Manager::Uninit()
{
	Renderer::Uninit();
}

void Manager::Update()
{

}

void Manager::Draw()
{
	Renderer::Begin();


	Renderer::End();
}
