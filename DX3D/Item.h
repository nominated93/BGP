#pragma once

enum eMouseState
{
	NORMAL,
	MOUSEOVER,
	SELECTED,
	SELECTEDMOVE,
	COUNT
};

class SkinnedMesh;
class UIImage;
class IUIObject;
class Item : public IDisplayObject
{
private:
	SkinnedMesh *	m_pSkinnedMesh;
	BoundingSphere	m_tCollisionSphere;
	LPD3DXMESH		m_pMesh;
	UIImage*		m_pIconImage;
	UIImage*		m_pIconBackGroundImage;

	LPD3DXSPRITE	m_pSprite;
	ITEM_LIST		m_tItemName;
	eMouseState		m_eMouseState;

private:
	bool		m_isCollision;
	bool		m_isPick;

public:
	ITEM_INTO		m_tItemInto;
	IUIObject*		m_pRootIcon;
public:
	Item();
	~Item();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Init(char* fileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL, ITEM_INTO II);
	virtual void Update() override;
	virtual void Render() override;

public:
	void MouseDrag(bool isClick);
	void IconUpdate();
	void IconRender();
public:

	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere; }

	ITEM_LIST GetItemName() { return m_tItemName; }
	void SetItemName(ITEM_LIST tItemName) { m_tItemName = tItemName; }

	UIImage* GetPIconImage() { return m_pIconImage; }

	UIImage* GetPBGIconImage() { return m_pIconBackGroundImage; }

	bool GetIsCollision() { return m_isCollision; }
	void SetIsCollision(bool isCollision) { m_isCollision = isCollision; }


};

