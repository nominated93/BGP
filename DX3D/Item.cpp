#include "stdafx.h"
#include "Item.h"
#include "SkinnedMesh.h"
#include "UIImage.h"

Item::Item() :
	m_pSkinnedMesh(NULL),
	m_pIconImage(NULL),
	m_isCollision(false)
{
}


Item::~Item()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_DELETE(m_pIconImage);
}



void Item::Init()
{
	//m_pSkinnedMesh = new SkinnedMesh();
	m_pIconImage = new UIImage(m_pSprite);

}

void Item::Init(char* fileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot , ITEM_LIST IL, ITEM_INTO II)
{
	m_pSkinnedMesh = new SkinnedMesh();
	m_pIconImage = new UIImage(m_pSprite);


	m_pos = pos;
	m_rot = rot;
	m_pSkinnedMesh->Setup("resources/weapons", fileName);
	m_tItemName = IL;
	m_tItemInto = II;

	m_tCollisionSphere.center = m_pos;
	m_tCollisionSphere.radius = 20;
	D3DXCreateSphere(g_pDevice, m_tCollisionSphere.radius, 10, 10, &m_pMesh, NULL);

}

void Item::Update()
{
	m_tCollisionSphere.center = m_pos;
}

void Item::Render()
{
	D3DXMATRIXA16 matS, matR, matT, matWorld;

	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	D3DXMatrixIdentity(&matT);

	//m_baseRotY = g_pCamera->m_rotY;

	D3DXMatrixRotationY(&matR, m_rot.y);
	D3DXMatrixRotationX(&matR, D3DX_PI/2);

	//Debug->AddText(m_rot.y);
	//D3DXVec3TransformNormal(&m_rot, &m_rot, &matR);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	//D3DXMatrixIdentity(&matS);

	matWorld = matS * matR * matT;

	//g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);

	m_pSkinnedMesh->Render(NULL, &matWorld);
	m_pMesh->DrawSubset(0);
	Debug->AddText("isC : ");
	Debug->AddText(m_isCollision);
	Debug->EndLine();
}

void Item::MouseDrag()
{
	RECT rect;
	D3DXMATRIXA16 mat;
	m_pSprite->GetTransform(&mat);

	int left = mat._41 + m_pIconImage->m_combinedPos.x;
	int top = mat._42 + m_pIconImage->m_combinedPos.y;
	int right = left + m_pIconImage->m_size.x;
	int bottom = top + m_pIconImage->m_size.y;

	SetRect(&rect, left, top, right, bottom);

	

	POINT mousePoint;
	GetCursorPos(&mousePoint);
	ScreenToClient(g_hWnd, &mousePoint);

	//마우스 포인터가 영역 안에 있을 때
	if (PtInRect(&rect, mousePoint))
	{
		/*if (g_pKeyboardManager->isOnceKeyDown(VK_LBUTTON)
		{
			if (m_buttonState == MOUSEOVER)
			{
				m_buttonState = SELECTED;
			}
		}
		else
		{
			if (m_buttonState == SELECTED)
			{
				if (m_pDelegate)
					m_pDelegate->OnClick(this);
			}
			m_buttonState = MOUSEOVER;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{

		}
		else
		{
			m_buttonState = NORMAL;
		}*/
	}
}
