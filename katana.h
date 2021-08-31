#pragma once
#include "weapon.h"

class Katana :public Weapon
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