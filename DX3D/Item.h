#pragma once
#include "IDisplayObject.h"
class SkinnedMesh;
class Item : public IDisplayObject
{
private:
	SkinnedMesh *	m_pSkinnedMesh;
	BoundingSphere	m_tCollisionSphere;
	LPD3DXMESH		m_pMesh;
	ITEM_LIST		m_tItemList;

private:
	bool		m_isCollision;
	

public:
	Item();
	~Item();

	// IDisplayObject을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Init(char* fileName,D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEM_LIST IL);
	virtual void Update() override;
	virtual void Render() override;

public:
	bool GetIsCollision() { return m_isCollision; }
	void SetIsCollision(bool isCollision) { m_isCollision = isCollision; }

	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere; }
	ITEM_LIST GetItemList() { return m_tItemList; }
};

