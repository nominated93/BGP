#include "stdafx.h"
#include "Equipment.h"


Equipment::Equipment()
{
}


Equipment::~Equipment()
{
}

void Equipment::Init()
{
	m_pEquipmentUI = new UIImage(m_pSprite);
	m_pEquipmentUI->SetTexture("resources/ui/UI_PLAYER.png");
	m_pRootUI = m_pEquipmentUI;
	m_pEquipmentUI->SetPosition(&D3DXVECTOR3(100, 0, 0));
}

void Equipment::Update()
{
	if (g_pKeyboardManager->isOnceKeyDown('T'))
	{
		m_isEquipmentUI = !m_isEquipmentUI;
	}

	if (m_isEquipmentUI)
	{
		SAFE_UPDATE(m_pRootUI);
		EquipmentItemUIUpdate();
	}
}

void Equipment::Render()
{
	//g_pDevice->SetTexture(0, NULL);

	if (m_isEquipmentUI)
	{
		SAFE_RENDER(m_pRootUI);
		EquipmentItemUIRender();
	}
}

void Equipment::OnClick(UIButton * pSender)
{
}

void Equipment::AddItemToEquipment(ITEM_LIST IL)
{
}

void Equipment::EquipmentItemUIUpdate()
{
}

void Equipment::EquipmentItemUIRender()
{
}
