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
	ItemSetup("AK-47.X", D3DXVECTOR3(10, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47,ITEM_INTO::FIELD);
	ItemSetup("AK-47.X", D3DXVECTOR3(6, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(-5, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(12, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("AK-47.X", D3DXVECTOR3(8, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(-3, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(12, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("AK-47.X", D3DXVECTOR3(8, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(-3, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(15, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("AK-47.X", D3DXVECTOR3(15, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(15, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);

	ItemSetup("AK-47.X", D3DXVECTOR3(3, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("AK-47.X", D3DXVECTOR3(15, 1, -6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47, ITEM_INTO::FIELD);
	ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(15, 1, -3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR, ITEM_INTO::FIELD);
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
