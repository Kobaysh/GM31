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
#include "audio.h"
#include "texture.h"
#include "title.h"
#include "game.h"


void Title::Init()
{
	m_IsFading = false;
	m_Timer = 0.0f;
	m_ParticleTimer = 0.0f;
	AppendGameObject<TitleBG>(GameObject::GOT_OBJECT2D);
	AppendGameObject<TitleLogo>(GameObject::GOT_OBJECT2D);
	AppendGameObject<PressSpaceKey>(GameObject::GOT_OBJECT2D);
	AppendGameObject<Fade>(GameObject::GOT_OBJECT2D);
	TitleParticle::Create(0.0f);
	Audio* bgm = AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	bgm->Load("asset\\audio\\bgm\\title.wav");

	bgm->Play(0.3f , true);

	m_DecisionSE = ManagerT::GetScene()->AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	m_DecisionSE->Load("asset\\audio\\se\\decision.wav");
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
		// ƒV[ƒ“‘JˆÚ
		if (!m_IsFading)
		{
			Fade::SetFade(Fade::FADE_OUT);
			m_IsFading = true;
			m_DecisionSE->Play();
		}
	}
	if (m_IsFading) {
		if (Fade::GetFadeType() == Fade::FADE_NONE) {
			ManagerT::SetScene<Game>();
			m_IsFading = false;
		}
	}
	m_Timer += 0.01f;
	m_ParticleTimer += 0.01f;
	if (m_ParticleTimer > 2.0f)
	{
		float offsetY = cosf(m_Timer) * 0.5f * SCREEN_HEIGHT;
		TitleParticle::Create(offsetY);
		m_ParticleTimer = 0.0f;
	}
}