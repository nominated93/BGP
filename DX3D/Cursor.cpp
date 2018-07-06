#include "stdafx.h"
#include "Cursor.h"


Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}

void Cursor::Init()
{
	m_pCursorImg = new UIImage(m_pSprite);
	m_pCursorImg->SetTexture("resources/cursor/Point.png");
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);
	m_pCursorImg->SetPosition(&D3DXVECTOR3(mousePoint.x, mousePoint.y, 0));
}

void Cursor::Update()
{
	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);
	m_pCursorImg->SetPosition(&D3DXVECTOR3(mousePoint.x, mousePoint.y, 0));
	m_pCursorImg->Update();
}

void Cursor::Render()
{
	m_pCursorImg->Render();
}
