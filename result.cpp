#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "keylogger.h"
#include "gameObject.h"
#include "polygon2D.h"


#include "result.h"

void Result::Init()
{
	AppendGameObject<Polygon2D>(GameObject::GOT_OBJECT2D);

}

void Result::Uninit()
{
	Scene::Uninit();
}
