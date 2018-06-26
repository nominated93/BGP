#pragma once
#include "IDisplayObject.h"

class Item;
class ItemManager : public IDisplayObject
{
private:
	vector<Item*> m_vecItem;
	vector<Item*>::iterator m_iterItem;

public:
	ItemManager();
	~ItemManager();

	void Init();
	void Update();
	void Render();

	void ItemSetup(char* fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL);
public:
	vector<Item*>* GetPVecItem() { return &m_vecItem; }
};

