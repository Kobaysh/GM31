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
	m_ExplaMove = new ExplaMove();
	m_ExplaMove->Init();
	m_ExplaAtk = new ExplaAtk();
	m_ExplaAtk->Init();
	m_ExplaDef = new ExplaDef();
	m_ExplaDef->Init();
	m_ExplaLock = new ExplaLock();
	m_ExplaLock->Init();
	m_ExplaChange = new ExplaChange();
	m_ExplaChange->Init();
}

void ExplanationGame::Uninit()
{
	m_ExplaMove->Uninit();
	delete m_ExplaMove;
	m_ExplaAtk->Uninit();
	delete m_ExplaAtk;
	m_ExplaDef->Uninit();
	delete m_ExplaDef;
	m_ExplaLock->Uninit();
	delete m_ExplaLock;
	m_ExplaChange->Uninit();
	delete m_ExplaChange;
}

void ExplanationGame::Update()
{
}

void ExplanationGame::Draw()
{
	m_ExplaMove->Draw();
	m_ExplaAtk->Draw();
	m_ExplaDef->Draw();
	m_ExplaLock->Draw();
	m_ExplaChange->Draw();
}

