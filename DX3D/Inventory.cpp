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
	m_pInvenUI->SetTexture("resources/ui/ui-bankframe.png");
	m_pRootUI = m_pInvenUI;
	m_pInvenUI->SetPosition(&D3DXVECTOR3(950, 0, 0));



	m_pInvenExitUI = new UIButton(this,m_pSprite, INVENUI_EXIT);
	m_pInvenExitUI->SetTexture("resources/ui/UI-Panel-MinimizeButton-Disabled.png",
		"resources/ui/UI-Panel-MinimizeButton-Up.png",
		"resources/ui/UI-Panel-MinimizeButton-Down.png");
	m_pRootUI->AddChild(m_pInvenExitUI);

	m_pInvenExitUI->SetPosition(&D3DXVECTOR3(371, 7, 0));
}

void Inventory::Update()
{
	

	//ÀÎº¥Ã¢ ¶ç¿ì±â
	if (g_pKeyManager->isOnceKeyDown('I'))
	{
		g_pCamera->SetIsAngleMove(!(g_pCamera->GetIsAngleMove()));
		m_isInvenUI = !m_isInvenUI;
	}

	if (m_isInvenUI)
	{
		SAFE_UPDATE(m_pRootUI);
		ItemIconImageUpdate();
		m_pCursor->Update();
	
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
	if (pSender->m_uiTag == INVENUI_EXIT)
	{
		g_pCamera->SetIsAngleMove(!(g_pCamera->GetIsAngleMove()));
		m_isInvenUI = !m_isInvenUI;
	}
}

void Inventory::AddItemToInven(ITEM_LIST IL)
{
	D3DXVECTOR3 vFirstDeltaPos(44, 75, 0);
	D3DXVECTOR3 vDeltaPos(44, 75, 0);


	int iDeltaX = 48;
	int iDeltaY = 46;
		
	if (m_vecInvenItemIcon.size())
	{
		vDeltaPos.x = vDeltaPos.x + (m_vecInvenItemIcon.size() % 7) * iDeltaX;
		vDeltaPos.y = vDeltaPos.y + (m_vecInvenItemIcon.size() / 7) * iDeltaY;
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
