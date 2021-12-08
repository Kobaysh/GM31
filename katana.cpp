#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "katana.h"

int Katana::m_modelId = Model::MODEL_INVALID_ID;
const char* Katana::m_modelFileName = "";

Katana::Katana()
{
}

Katana::~Katana()
{
}

void Katana::Init()
{
	if (m_modelId == Model::MODEL_INVALID_ID)
	{
		m_modelId = Model::SetModelLoadfile(m_modelFileName);
	}
}

void Katana::Uninit()
{
}

void Katana::Update()
{
}

void Katana::Draw()
{
	Model::Draw(m_modelId);
}
void Katana::Load()
{
	Model::Load(m_modelId);
}

void Katana::UnLoad()
{
	Model::Release(m_modelId);
}