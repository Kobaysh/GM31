#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "keylogger.h"
#include "gameObject.h"
#include "polygon2D.h"
#include "resultLogo.h"
#include "resultBG.h"
#include "fade.h"
#include "pressSpaceKey.h"

#include "title.h"
#include "result.h"

void Result::Init()
{
	AppendGameObject<ResultBG>(GameObject::GOT_OBJECT2D);
	AppendGameObject<ResultLogo>(GameObject::GOT_OBJECT2D);
	AppendGameObject<PressSpaceKey>(GameObject::GOT_OBJECT2D);
	AppendGameObject<Fade>(GameObject::GOT_OBJECT2D);

	m_IsFading = false;
	Fade::SetFade(Fade::FADE_IN);
}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();
	if (!m_IsFading && KeyLogger_Trigger(KL_DICISION) || KeyLogger_Trigger(KL_JUMP)) {
		// ÉVÅ[ÉìëJà⁄
		Fade::SetFade(Fade::FADE_OUT);
		m_IsFading = true;
	}

	if (m_IsFading) {
		if (Fade::GetFadeType() == Fade::FADE_NONE) {
			ManagerT::SetScene<Title>();
			m_IsFading = false;
		}
	}
}
