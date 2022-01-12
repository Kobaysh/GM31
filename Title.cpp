#include "main.h"
#include "manager.h"
#include "renderer.h"

#include "keylogger.h"
#include "gameObject.h"

#include "titleBG.h"
#include "titleLogo.h"
#include "fade.h"
#include "pressSpaceKey.h"
#include "titleParticle.h"
#include "texture.h"
#include "title.h"
#include "game.h"


void Title::Init()
{
	m_isFading = false;
	m_timer = 0.0f;
	m_particleTimer = 0.0f;
	AppendGameObject<TitleBG>(GameObject::GOT_OBJECT2D);
	AppendGameObject<TitleLogo>(GameObject::GOT_OBJECT2D);
	AppendGameObject<PressSpaceKey>(GameObject::GOT_OBJECT2D);
	AppendGameObject<Fade>(GameObject::GOT_OBJECT2D);
	TitleParticle::Create(0.0f);
	Fade::SetFade(Fade::FADE_IN);
}

void Title::Uninit()
{
	Scene::Uninit();
	TitleParticle::Unload();
	Texture::AllRelease();
}

void Title::Update()
{
	Scene::Update();
	if (KeyLogger_Trigger(KL_DICISION) || KeyLogger_Trigger(KL_JUMP))
	{
		// ÉVÅ[ÉìëJà⁄
		if (!m_isFading)
		{
			Fade::SetFade(Fade::FADE_OUT);
			m_isFading = true;
		}
	}
	if (m_isFading) {
		if (Fade::GetFadeType() == Fade::FADE_NONE) {
			ManagerT::SetScene<Game>();
			m_isFading = false;
		}
	}
	m_timer += 0.01f;
	m_particleTimer += 0.01f;
	if (m_particleTimer > 2.0f)
	{
		float offsetY = cosf(m_timer) * 0.5f * SCREEN_HEIGHT;
		TitleParticle::Create(offsetY);
		m_particleTimer = 0.0f;
	}
}