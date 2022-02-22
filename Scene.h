#pragma once
#include <list>
#include <vector>
#include <typeinfo>
#include "gameObject.h"

// �V�[���C���^�[�t�F�[�X
class Scene
{
protected:
	std::list<GameObject*> m_GameObject[GameObject::GOT_MAX];	// STL�̃��X�g�\��
	bool m_IsFading;											// �t�F�[�h�����ǂ���
public:
	Scene(){}
	virtual ~Scene(){}

	// �Q�[���I�u�W�F�N�g�Ǘ����ɒǉ�
	template <typename TS>
	TS* AppendGameObject(GameObject::GameObject_Type type) {
		TS* gameObject = new TS();
		gameObject->Init();
		m_GameObject[type].push_back(gameObject);
		return gameObject;
	}
	template<typename T>
	T* AddGameObject(T* pObj, GameObject::GameObject_Type type) {
		if (pObj == nullptr)return nullptr;
		pObj->Init();
		m_GameObject[type].push_back(pObj);
		return pObj;
	}
	GameObject* AddGameObject(GameObject* pObj, GameObject::GameObject_Type type) {
		if (pObj == nullptr)return nullptr;
		pObj->Init();
		m_GameObject[type].push_back(pObj);
		return pObj;
	}

	// �Q�[���I�u�W�F�N�g�C���X�^���X�Q�b�^�[
	template<typename TS>
	TS* GetGameObject(GameObject::GameObject_Type type) {

		for (GameObject*object : m_GameObject[type]) {
			if (typeid(*object) == typeid(TS)) {	// �^�𒲂ׂ�(RTTI���I�^���)
				return (TS*)object;
			}
		}

		return nullptr;
	}

	template<typename TS>
	std::vector<TS*> GetGameObjects(GameObject::GameObject_Type type) {
		std::vector<TS*> objects;
			for (GameObject* object : m_GameObject[type]) {
				if (typeid(*object) == typeid(TS)) {
					objects.push_back((TS*)object);
				}
			}
		return objects;
	}

	// ������
	virtual void Init() = 0;

	// �I������
	virtual void Uninit() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear();	// ���X�g�̃N���A
		}
	}

	// �X�V����
	virtual void Update() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Update();
			}
			// forroop�̊O�łȂ��ƃ_��
			m_GameObject[i].remove_if(
				[](GameObject* object) {
					return object->Destroy();
				}
			);
			// �����_��	
		}
	}
	// �`�揈��
	virtual void Draw() {
		for (int i = 0; i < GameObject::GOT_MAX; i++) {
			for (GameObject* object : m_GameObject[i]) {
				object->Draw();
			}
		}
	}
};

