#pragma once
#include "weapon.h"
#include "gameObject.h"

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
	static int m_modelId;
	static const char* m_modelFileName;
};