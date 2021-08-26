#include "main.h"
#include "manager.h"
#include "renderer.h"


#include "gameObject.h"
#include "obb.h"
#include "polygon2D.h"
#include "camera.h"
#include "field.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "sky.h"
#include "rock.h"
#include "audio.h"
#include "keylogger.h"
#include "result.h"

#include "game.h"

void Game::Init()
{
	Bullet::Load();
	AppendGameObject<Camera>(GameObject::GOT_CAMERA);
	AppendGameObject<Field>(GameObject::GOT_OBJECT3D);
	AppendGameObject<Sky>(GameObject::GOT_OBJECT3D);
	AppendGameObject<Player>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, -4.0f));
	AppendGameObject<Polygon2D>(GameObject::GOT_OBJECT2D);
	for (int i = 0; i < 20; i++) {
		XMFLOAT3 pos;
		XMFLOAT3 scl;
		scl.x = scl.y = scl.z = (float)rand() / RAND_MAX * 3.0f + 2.0f;
		pos.x = (float)rand() / RAND_MAX * 100.f - 50.f;
		pos.z = (float)rand() / RAND_MAX * 100.f - 100.f;
		pos.y = 0.0f + scl.y / 2;
		Rock* rock = AppendGameObject<Rock>(GameObject::GOT_OBJECT3D);
		rock->SetPosition(pos);
		rock->SetRotation(pos);
		rock->SetScale(scl);
	}
	AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(5.0f, 1.0f, 1.0f));
	AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, 1.0f));
	AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(-5.0f, 1.0f, 1.0f));

	Audio* bgm = AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	bgm->Load("asset\\audio\\bgm\\bgm.wav");
	
	bgm->Play(0.1f , true);
}

void Game::Uninit()
{
	Scene::Uninit();	// �p�����N���X�̃��\�b�h�Ăяo��(static���\�b�h�Ə���������)
	Bullet::UnLoad();
	Model::Uninit();
}

void Game::Update()
{
	Scene::Update();

	if (KeyLogger_Trigger(KL_RESET)) {	// R�L�[?
		std::vector<Enemy*>  enemy = Scene::GetGameObjects<Enemy>(GameObject::GOT_OBJECT3D);
		if(enemy.empty()){

		// �V�[���J��
		ManagerT::SetScene<Result>();
		}
	}
}
