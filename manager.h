#pragma once
#include "Singleton.h"

class Manager : public Singleton
{
private:
	Manager() = default;
	~Manager() = default;

	static Manager* instance;

public:
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
	Manager(Manager&&) = delete;
	Manager& operator=(Manager&&) = delete;

	static Manager& GetInstance() {
		return *instance;
	}

	static void create() {
		if (!instance) {
			instance = new Manager;
		}
	}

	static void Destroy() {
		delete instance;
		instance = NULL;
	}


	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

};

//
//class ManagerT : public Singleton<ManagerT>
//{
//public:
//	friend class Singleton<ManagerT>; // Singleton �ł̃C���X�^���X�쐬�͋���
//public:
//	static void Init();
//	static void Uninit();
//	static void Update();
//	static void Draw();
//protected:
//	ManagerT();	// �O���ł̃C���X�^���X�쐬�͋֎~
//	virtual ~ManagerT();
//};