#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "keylogger.h"
#include "gameObject.h"
//#include "camera.h"
//#include "polygon2D.h"
#include "titleLogo.h"

#include "title.h"
#include "game.h"


void Title::Init()
{
	/*Camera* pCamera = new Camera(false);
	AddGameObject(pCamera, GameObject::GOT_CAMERA);*/
	//AppendGameObject<Polygon2D>(GameObject::GOT_OBJECT2D);
	AppendGameObject<TitleLogo>(GameObject::GOT_OBJECT2D);
}

void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();
	if (KeyLogger_Trigger(KL_DICISION)) {
		// ÉVÅ[ÉìëJà⁄
		ManagerT::SetScene<Game>();
	}
}
