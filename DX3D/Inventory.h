#pragma once

#include "UIButton.h"
#include "UIImage.h"
#include "IUIObject.h"



enum INVENUI
{
	INVENUI_EXIT,
	INVENUI_NONE
};

class Cursor;
class Equipment;
class Item;
class Inventory : public IDisplayObject, public IUIButtonDelegate
{
private:
	UIImage *		m_pInvenUI;
	UIImage *		m_pInvenUI2;
	UIButton *		m_pInvenExitUI;
	LPD3DXSPRITE	m_pSprite;
	IUIObject*		m_pRootUI;
	Equipment*		m_pEquipment;
	Cursor*			m_pCursor;

private:
	vector<Item*> m_vecInvenItemIcon;
	vector<Item*>::iterator m_iterInvenItemIcon;

private:
	bool m_isInvenUI;

public:
	Inventory();
	~Inventory();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnClick(UIButton * pSender) override;

public:
	void AddItemToInven(ITEM_LIST IL);
	void RemoveItemFromInven();
	void ItemIconImageUpdate();
	void ItemIconImageRender();

public:
	vector<Item*> GetVecInvenItemIcon() { return m_vecInvenItemIcon; }

};

