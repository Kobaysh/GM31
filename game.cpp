#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "myImGui.h"

#include "gameObject.h"
#include "texture.h"
#include "obb.h"
#include "polygon2D.h"
#include "camera.h"
#include "debugCamera.h"
#include "field.h"
#include "meshField.h"
#include "model.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "sky.h"
#include "rock.h"
#include "wood.h"
#include "wall.h"
#include "audio.h"
#include "keylogger.h"
#include "result.h"
#include "fade.h"
#include "pressSpaceKey.h"

#include "game.h"


#define FIELD_XZ (20)
#define FIELD__SCALE_XZ (20)

void Game::Init()
{
	m_isFading = false;
	m_isGameClear = false;

	Bullet::Load();
	//Camera* camera = new Camera();
	//camera->Init(true, false);
	//AddGameObject(camera, GameObject::GOT_CAMERA);
	AppendGameObject<Camera>(GameObject::GOT_CAMERA)->Init(true, false);
	AppendGameObject<DebugCamera>(GameObject::GOT_CAMERA)->Init(false, false);


//	AppendGameObject<Field>(GameObject::GOT_OBJECT3D);
	
	MeshField* meshField = new MeshField();
	meshField->Init(XMFLOAT3(0.0f, 0.0f, 0.0f), FIELD_XZ, FIELD_XZ, FIELD__SCALE_XZ, FIELD__SCALE_XZ);
	AddGameObject(meshField , GameObject::GOT_OBJECT3D);

//	AppendGameObject<MeshField>(GameObject::GOT_OBJECT3D);

	AppendGameObject<Sky>(GameObject::GOT_OBJECT3D);
	AppendGameObject<Player>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, -4.0f));
//	AppendGameObject<Polygon2D>(GameObject::GOT_OBJECT2D);
	for (int i = 0; i < 20; i++) {
		XMFLOAT3 pos;
		XMFLOAT3 scl;
		scl.x = scl.y = scl.z = (float)rand() / RAND_MAX * 3.0f + 2.0f;
		pos.x = (float)rand() / RAND_MAX * 100.f - 40.f;
		pos.z = (float)rand() / RAND_MAX * 100.f - 100.f;
		pos.y = 0.0f + scl.y / 2;
		AppendGameObject<Rock>(GameObject::GOT_OBJECT3D)->Init(pos, pos, scl);

		Wood* wood = AppendGameObject<Wood>(GameObject::GOT_OBJECT2D);
		pos.x = (float)rand() / RAND_MAX * 100.f - 50.f;
		pos.z = (float)rand() / RAND_MAX * 100.f - 50.f;
		pos.y = 0.0f + 2.5f;
		wood->SetPosition(pos);
		wood->SetScale(XMFLOAT3(5.0f, 5.0f, 1.0f));
		
	}
	//XMFLOAT3 pos = XMFLOAT3(-1.0f,0.0f,-1.0f);
	//XMFLOAT3 scl = XMFLOAT3(1.0f,1.0f,1.0f);
	//AppendGameObject<Rock>(GameObject::GOT_OBJECT3D)->Init(pos, pos, scl);

	//AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(15.0f, 1.0f, 10.0f));
	//AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, 1.0f));
	//AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(-15.0f, 1.0f, 7.0f));
	//AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(-5.0f, 1.0f, 2.0f));
	AppendGameObject<Enemy>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(0.0f, 1.0f, 5.0f));

	AppendGameObject<Wall>(GameObject::GOT_OBJECT3D)->SetPosition(XMFLOAT3(5.0f, 1.0f, 5.0f));

	AppendGameObject<Fade>(GameObject::GOT_OBJECT2D);
	Fade::SetFade(Fade::FADE_IN);

	MyImGui::Init(GetWindow());

	Audio* bgm = AppendGameObject<Audio>(GameObject::GOT_OBJECT2D);
	bgm->Load("asset\\audio\\bgm\\bgm.wav");
	
	bgm->Play(0.0f , true);
}

void Game::Uninit()
{
	Scene::Uninit();	// 継承元クラスのメソッド呼び出し(staticメソッドと書き方同じ)
	MyImGui::Uninit();
	Bullet::UnLoad();
	Texture::AllRelease();
	Model::Uninit();
}

void Game::Update()
{
	Scene::Update();
	std::vector<Enemy*>  enemy = Scene::GetGameObjects<Enemy>(GameObject::GOT_OBJECT3D);
	if (enemy.empty()) {
		if (!m_isGameClear) {
			AppendGameObject<PressSpaceKey>(GameObject::GOT_OBJECT2D);
			AppendGameObject<Fade>(GameObject::GOT_OBJECT2D);
			m_isGameClear = true;
		}
		if (!m_isFading && KeyLogger_Trigger(KL_DICISION) || KeyLogger_Trigger(KL_JUMP)) {	// 決定キーかスペースキー

			// シーン遷移
			Fade::SetFade(Fade::FADE_OUT);
			m_isFading = true;

		}
		if (m_isFading) {
			if (Fade::GetFadeType() == Fade::FADE_NONE) {
				ManagerT::SetScene<Result>();
				m_isFading = false;
				return;
			}
		}
	}

}

void Game::Draw()
{
	MyImGui::Update();
	Scene::Draw();
	MyImGui::StartRender();
}
