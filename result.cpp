#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "keylogger.h"
#include "gameObject.h"
#include "polygon2D.h"
#include "resultLogo.h"


#include "title.h"
#include "result.h"

void Result::Init()
{
	AppendGameObject<ResultLogo>(GameObject::GOT_OBJECT2D);

}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();
	if (KeyLogger_Trigger(KL_DICISION)) {
		// �V�[���J��
		ManagerT::SetScene<Title>();
	}
}
