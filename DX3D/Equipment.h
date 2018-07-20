#pragma once

#include "UIButton.h"
#include "UIImage.h"
#include "IUIObject.h"

class Item;

class Equipment : public IDisplayObject, public IUIButtonDelegate
{
private:
	UIImage *		m_pEquipmentIcon;
	LPD3DXSPRITE	m_pSprite;

public:
	Equipment();
	~Equipment();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnClick(UIButton * pSender) override;

private:
	vector<Item*> m_vecEquipmentItemIcon;
	vector<Item*>::iterator m_iterEquipmentItemIcon;

private:
	bool m_isEquipmentUI;

public:
	void AddItemToEquipment(ITEM_LIST IL);
	void EquipmentItemIconUpdate();
	void EquipmentItemIconRender();

public:
	vector<Item*> GetVecInvenItemIcon() { return m_vecEquipmentItemIcon; }
};

