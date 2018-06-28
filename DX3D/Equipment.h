#pragma once

#include "UIButton.h"
#include "UIImage.h"
#include "IUIObject.h"

class Equipment : public IDisplayObject, public IUIButtonDelegate
{
private:
	UIImage * m_pEquipmentUI;
	LPD3DXSPRITE	m_pSprite;
	IUIObject*		m_pRootUI;
public:
	Equipment();
	~Equipment();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	virtual void OnClick(UIButton * pSender) override;

private:
	vector<UIImage*> m_vecEquipmentItemUI;
	vector<UIImage*>::iterator m_iterEquipmentItemUI;

private:
	bool m_isEquipmentUI;

public:
	void AddItemToEquipment(ITEM_LIST IL);
	void EquipmentItemUIUpdate();
	void EquipmentItemUIRender();

public:
	vector<UIImage*> GetVecInvenItemUI() { return m_vecEquipmentItemUI; }
};

