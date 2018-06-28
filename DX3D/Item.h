#pragma once

class SkinnedMesh;
class UIImage;
class Item : public IDisplayObject
{
private:
	SkinnedMesh *	m_pSkinnedMesh;
	BoundingSphere	m_tCollisionSphere;
	LPD3DXMESH		m_pMesh;
	UIImage*		m_pIconImage;
	LPD3DXSPRITE	m_pSprite;
	ITEM_LIST		m_tItemName;

private:
	bool		m_isCollision;
	
public:
	ITEM_INTO		m_tItemInto;
public:
	Item();
	~Item();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Init(char* fileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL, ITEM_INTO II);
	virtual void Update() override;
	virtual void Render() override;

private:


public:
	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere; }

	ITEM_LIST GetItemName() { return m_tItemName; }

	UIImage* GetPIconImage() { return m_pIconImage; }

	bool GetIsCollision() { return m_isCollision; }
	void SetIsCollision(bool isCollision) { m_isCollision = isCollision; }


};

