#include "main.h"
#include "renderer.h"
#include "explaMove.h"
#include "explaAtk.h"
#include "explaDef.h"
#include "explaLock.h"
#include "explaChange.h"
#include "explanationOps.h"
#include "texture.h"
#include "input.h"


void ExplanationGame::Init()
{
	m_explaMove = new ExplaMove();
	m_explaMove->Init();
	m_explaAtk = new ExplaAtk();
	m_explaAtk->Init();
	m_explaDef = new ExplaDef();
	m_explaDef->Init();
	m_explaLock = new ExplaLock();
	m_explaLock->Init();
	m_explaChange = new ExplaChange();
	m_explaChange->Init();
}

void ExplanationGame::Uninit()
{
	m_explaMove->Uninit();
	delete m_explaMove;
	m_explaAtk->Uninit();
	delete m_explaAtk;
	m_explaDef->Uninit();
	delete m_explaDef;
	m_explaLock->Uninit();
	delete m_explaLock;
	m_explaChange->Uninit();
	delete m_explaChange;
}

void ExplanationGame::Update()
{
}

void ExplanationGame::Draw()
{
	m_explaMove->Draw();
	m_explaAtk->Draw();
	m_explaDef->Draw();
	m_explaLock->Draw();
	m_explaChange->Draw();
}

