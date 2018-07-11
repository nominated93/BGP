#include "stdafx.h"
#include "Inventory.h"
#include "Equipment.h"
#include "Cursor.h"
#include "Item.h"

Inventory::Inventory():
	m_pInvenUI(NULL),
	m_pInvenExitUI(NULL),
	m_pEquipment(NULL),
	m_pCursor(NULL),
	m_pRootUI(NULL),
	m_isInvenUI(false)
{
}

Inventory::~Inventory()
{
	SAFE_RELEASE(m_pInvenUI);
	SAFE_RELEASE(m_pInvenExitUI);
	SAFE_RELEASE(m_pEquipment);
	SAFE_RELEASE(m_pCursor);
	m_pRootUI->ReleaseAll();
	m_vecInvenItemIcon.clear();
}

void Inventory::Init()
{
	m_pEquipment = new Equipment; m_pEquipment->Init();
	m_pCursor = new Cursor; m_pCursor->Init();

	m_pInvenUI = new UIImage(m_pSprite);
	m_pInvenUI->SetTexture("resources/ui/inventory.png");
	m_pRootUI = m_pInvenUI;
	m_pInvenUI->SetPosition(&D3DXVECTOR3(0, 0, 0));

	//m_pInvenExitUI = new UIButton(this,m_pSprite, INVENUI_EXIT);
	//m_pInvenExitUI->SetTexture("resources/ui/UI-Panel-MinimizeButton-Disabled.png",
	//	"resources/ui/UI-Panel-MinimizeButton-Up.png",
	//	"resources/ui/UI-Panel-MinimizeButton-Down.png");
	//m_pRootUI->AddChild(m_pInvenExitUI);

	//m_pInvenExitUI->SetPosition(&D3DXVECTOR3(371, 7, 0));
}

void Inventory::Update()
{
	

	//인벤창 띄우기
	if (g_pKeyboardManager->isOnceKeyDown('I'))
	{
		g_pCamera->SetIsAngleMove(!(g_pCamera->GetIsAngleMove()));
		m_isInvenUI = !m_isInvenUI;
	}

	if (m_isInvenUI)
	{
		SAFE_UPDATE(m_pRootUI);
		ItemIconImageUpdate();
		m_pCursor->Update();
	
		if (g_pKeyboardManager->isOnceKeyDown(VK_RBUTTON))
		{
			RemoveItemFromInven();
		}
	}

	m_pEquipment->Update();


}

void Inventory::Render()
{
	g_pDevice->SetTexture(0, NULL);

	if (m_isInvenUI)
	{
		SAFE_RENDER(m_pRootUI);
		ItemIconImageRender();
		m_pCursor->Render();
	}
	
	m_pEquipment->Render();
}

void Inventory::OnClick(UIButton * pSender)
{
	//if (pSender->m_uiTag == INVENUI_EXIT)
	//{
	//	g_pCamera->SetIsAngleMove(!(g_pCamera->GetIsAngleMove()));
	//	m_isInvenUI = !m_isInvenUI;
	//}
}

void Inventory::AddItemToInven(ITEM_LIST IL)
{
	D3DXVECTOR3 vDeltaPos(71, 97, 0);

	int iDeltaX = 53;
	int iDeltaY = 51;
		
	if (m_vecInvenItemIcon.size())
	{
		vDeltaPos.x = vDeltaPos.x + (m_vecInvenItemIcon.size() % 5) * iDeltaX;
		vDeltaPos.y = vDeltaPos.y + (m_vecInvenItemIcon.size() / 5) * iDeltaY;
	}

	switch (IL)
	{
	case ITEM_LIST::AK47:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->GetPIconImage()->SetTexture("resources/ui/Attack.png");
		
		CItem->GetPIconImage()->SetPosition(&vDeltaPos);
		m_pRootUI->AddChild(CItem->GetPIconImage());

		m_vecInvenItemIcon.push_back(CItem);
	}
		break;

	case ITEM_LIST::ARMOR:
	{
		Item * CItem;
		CItem = new Item();
		CItem->Init();
		CItem->GetPIconImage()->SetTexture("resources/ui/FishingCursor.png");
		m_pRootUI->AddChild(CItem->GetPIconImage());
		CItem->GetPIconImage()->SetPosition(&vDeltaPos);

		m_vecInvenItemIcon.push_back(CItem);
	}
		break;

	}
}

void Inventory::RemoveItemFromInven()
{
	int iNum = 0;	//vec번호

	for (m_iterInvenItemIcon = m_vecInvenItemIcon.begin(); m_iterInvenItemIcon != m_vecInvenItemIcon.end(); )
	{

		LPD3DXSPRITE pSprite;
		D3DXCreateSprite(g_pDevice, &pSprite);

		D3DXMATRIXA16 mat;

		pSprite->GetTransform(&mat);

		int left = mat._41 + (*m_iterInvenItemIcon)->GetPIconImage()->GetCombinedPosition().x;
		int top = mat._42 + (*m_iterInvenItemIcon)->GetPIconImage()->GetCombinedPosition().y;
		int right = left + (*m_iterInvenItemIcon)->GetPIconImage()->GetInfo().Width;
		int bottom = top + (*m_iterInvenItemIcon)->GetPIconImage()->GetInfo().Height;

		RECT rc;
		SetRect(&rc, left, top, right, bottom);

		POINT mousePoint;
		GetCursorPos(&mousePoint);
		ScreenToClient(g_hWnd, &mousePoint);

		if (PtInRect(&rc, mousePoint))
		{
			m_pRootUI->RemoveChild(iNum);
			m_iterInvenItemIcon = m_vecInvenItemIcon.erase(m_iterInvenItemIcon);

			int iDeltaX = 53;
			int iDeltaY = 51;
			for (int i = 0; i < m_vecInvenItemIcon.size(); i++)
			{
				D3DXVECTOR3 vDeltaPos(71, 97, 0);
				vDeltaPos.x = vDeltaPos.x + (i % 5) * iDeltaX;
				vDeltaPos.y = vDeltaPos.y + (i / 5) * iDeltaY;
				m_vecInvenItemIcon[i]->GetPIconImage()->SetPosition(&vDeltaPos);
			}
	
		
		}
		else
		{
			m_iterInvenItemIcon++;
			iNum++;
		}
	}
}

void Inventory::ItemIconImageUpdate()
{
	if (m_vecInvenItemIcon.size()>0)
	{
		for (m_iterInvenItemIcon = m_vecInvenItemIcon.begin(); m_iterInvenItemIcon != m_vecInvenItemIcon.end(); m_iterInvenItemIcon++)
		{
			(*m_iterInvenItemIcon)->GetPIconImage()->Update();
		}
	}
	
}

void Inventory::ItemIconImageRender()
{
	if (m_vecInvenItemIcon.size() > 0)
	{
		for (m_iterInvenItemIcon = m_vecInvenItemIcon.begin(); m_iterInvenItemIcon != m_vecInvenItemIcon.end(); m_iterInvenItemIcon++)
		{
			(*m_iterInvenItemIcon)->GetPIconImage()->Render();
		}
	}
}
