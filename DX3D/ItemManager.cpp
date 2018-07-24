#include "stdafx.h"
#include "ItemManager.h"
#include "Item.h"


ItemManager::ItemManager()
{
}


ItemManager::~ItemManager()
{
	m_vecItem.clear();
}

void ItemManager::Init()
{
	//아이템셋팅
	int iFixY = -87;
	int iFixX = -207;
	int iFixZ = -60;
	ItemSetup("AK-47.X", D3DXVECTOR3(iFixX + 10, iFixY, iFixZ + 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47,ITEM_INTO::FIELD);
	ItemSetup("F_Back_C_01_.X", D3DXVECTOR3(iFixX + 6, iFixY, iFixZ + 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::BACKPACK, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(iFixX - 5, iFixY, iFixZ + 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(iFixX + 12, iFixY, iFixZ + 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Back_C_01_.X", D3DXVECTOR3(iFixX + 8, iFixY, iFixZ + 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::BACKPACK, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(iFixX - 3, iFixY, iFixZ + 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(iFixX + 12, iFixY, iFixZ + 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Head_G_01.X", D3DXVECTOR3(iFixX + 8, iFixY, iFixZ + 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::HEAD, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(iFixX -3, iFixY, iFixZ + 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(iFixX + 15, iFixY, iFixZ + 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Head_G_01.X", D3DXVECTOR3(iFixX + 15, iFixY, iFixZ + 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::HEAD, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(iFixX + 15, iFixY, iFixZ + 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(iFixX + 3, iFixY, iFixZ + 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Head_G_01.X", D3DXVECTOR3(iFixX + 15, iFixY, iFixZ - 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::HEAD, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(iFixX + 15, iFixY, iFixZ - 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);
}

void ItemManager::Update()
{
	for (m_iterItem = m_vecItem.begin(); m_iterItem != m_vecItem.end(); m_iterItem++)
	{
		(*m_iterItem)->Update();
	}
}

void ItemManager::Render()
{
	for (m_iterItem = m_vecItem.begin(); m_iterItem != m_vecItem.end(); m_iterItem++)
	{
		(*m_iterItem)->Render();
	}
}

void ItemManager::ItemSetup(char * fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL, ITEM_INTO II)
{
	Item* pItem = new Item;
	pItem->Init(fileName, pos, rot,IL,II);

	m_vecItem.push_back(pItem);
}
