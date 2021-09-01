#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "keylogger.h"
#include "gameObject.h"

#include "titleLogo.h"
#include "fade.h"
#include "pressSpaceKey.h"
#include "title.h"
#include "game.h"


void Title::Init()
{

	AppendGameObject<TitleLogo>(GameObject::GOT_OBJECT2D);
	AppendGameObject<PressSpaceKey>(GameObject::GOT_OBJECT2D);
	AppendGameObject<Fade>(GameObject::GOT_OBJECT2D);
	m_isFading = false;
	Fade::SetFade(Fade::FADE_IN);
}

void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();
	if (!m_isFading && KeyLogger_Trigger(KL_DICISION) || KeyLogger_Trigger(KL_JUMP)) {
		// ÉVÅ[ÉìëJà⁄
		Fade::SetFade(Fade::FADE_OUT);
		m_isFading = true;
	}
	if (m_isFading) {
		if (Fade::GetFadeType() == Fade::FADE_NONE) {
			ManagerT::SetScene<Game>();
			m_isFading = false;
		}
	}
}
