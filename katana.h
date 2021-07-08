#pragma once
#include "gameObject.h"

class Katana :public GameObject
{
public:
	Katana();
	~Katana();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static void Load();
	static void UnLoad();

private:

};

Katana::Katana()
{
}

Katana::~Katana()
{
}