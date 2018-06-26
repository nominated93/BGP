#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory():
	m_pInvenUI(NULL),
	m_pInvenExitUI(NULL),
	m_pRootUI(NULL),
	m_isInvenUI(false)
{
}

Inventory::~Inventory()
{
	SAFE_RELEASE(m_pInvenUI);
	SAFE_RELEASE(m_pInvenExitUI);
	m_pRootUI->ReleaseAll();
	m_vecInvenItemUI.clear();
}

void Inventory::Init()
{
	
	m_pInvenUI = new UIImage(m_pSprite);
	m_pInvenUI->SetTexture("resources/ui/ui-bankframe.png");
	m_pRootUI = m_pInvenUI;
	m_pInvenUI->SetPosition(&D3DXVECTOR3(950, 0, 0));

	//m_pInvenUI2 = new UIImage(m_pSprite);
	//m_pInvenUI2->SetTexture("ui-bankframe.png");
	//m_pRootUI->AddChild(m_pInvenUI2);
	//m_pInvenUI2->SetPosition(&D3DXVECTOR3(100, 100, 0));

	m_pInvenExitUI = new UIButton(this,m_pSprite, INVENUI_EXIT);
	m_pInvenExitUI->SetTexture("resources/ui/UI-Panel-MinimizeButton-Disabled.png",
		"resources/ui/UI-Panel-MinimizeButton-Up.png",
		"resources/ui/UI-Panel-MinimizeButton-Down.png");
	m_pRootUI->AddChild(m_pInvenExitUI);
	//m_pRootUI = m_pInventoryExitUI;
	m_pInvenExitUI->SetPosition(&D3DXVECTOR3(371, 7, 0));
}

void Inventory::Update()
{
	

	//ÀÎº¥Ã¢ ¶ç¿ì±â
	if (g_pKeyManager->isOnceKeyDown('I'))
	{
		m_isInvenUI = !m_isInvenUI;
	}

	if (m_isInvenUI)
	{
		SAFE_UPDATE(m_pRootUI);
		InvenItemUIUpdate();
	}

	//m_pInventoryUI->Update();
	//m_pInventoryExitUI->Update();
}

void Inventory::Render()
{
	g_pDevice->SetTexture(0, NULL);

	if (m_isInvenUI)
	{
		SAFE_RENDER(m_pRootUI);
		InvenItemUIRender();
	}
	
	//m_pInventoryUI->Render();
	//m_pInventoryExitUI->Render();
}

void Inventory::OnClick(UIButton * pSender)
{
	if (pSender->m_uiTag == INVENUI_EXIT)
	{
		m_isInvenUI = !m_isInvenUI;
	}
}

void Inventory::AddItemToInven(ITEM_LIST IL)
{
	D3DXVECTOR3 vFirstDeltaPos(44, 75, 0);
	D3DXVECTOR3 vDeltaPos(44, 75, 0);


	int iDeltaX = 48;
	int iDeltaY = 46;
		
	if (m_vecInvenItemUI.size())
	{
		vDeltaPos.x = vDeltaPos.x + (m_vecInvenItemUI.size() % 7) * iDeltaX;
		vDeltaPos.y = vDeltaPos.y + (m_vecInvenItemUI.size() / 7) * iDeltaY;
	}

	switch (IL)
	{
	case ITEM_LIST::AK47:
	{
		UIImage * UIImg;
		UIImg = new UIImage(m_pSprite);
		UIImg->SetTexture("resources/ui/Attack.png");
		
		UIImg->SetPosition(&vDeltaPos);
		m_pRootUI->AddChild(UIImg);

		m_vecInvenItemUI.push_back(UIImg);
	}
		break;

	case ITEM_LIST::ARMOR:
	{
		UIImage * UIImg;
		UIImg = new UIImage(m_pSprite);
		UIImg->SetTexture("resources/ui/FishingCursor.png");
		m_pRootUI->AddChild(UIImg);
		UIImg->SetPosition(&vDeltaPos);

		m_vecInvenItemUI.push_back(UIImg);
	}
		break;

	}
}

void Inventory::InvenItemUIUpdate()
{
	if (m_vecInvenItemUI.size()>0)
	{
		//D3DXVECTOR3 vDeltaPos(44,75,0);
		for (m_iterInvenItemUI = m_vecInvenItemUI.begin(); m_iterInvenItemUI != m_vecInvenItemUI.end(); m_iterInvenItemUI++)
		{
			(*m_iterInvenItemUI)->Update();
			//(*m_iterInvenItemUI)->SetPosition(&vDeltaPos);
		}
	}
	
}

void Inventory::InvenItemUIRender()
{
	if (m_vecInvenItemUI.size() > 0)
	{
		for (m_iterInvenItemUI = m_vecInvenItemUI.begin(); m_iterInvenItemUI != m_vecInvenItemUI.end(); m_iterInvenItemUI++)
		{
			(*m_iterInvenItemUI)->Render();
		}
	}
}
