#pragma once
#include "IUnitObject.h"

class SkinnedMesh;

class Player : public IUnitObject
{

private:
	SkinnedMesh*	m_pSkinnedMesh;
	BoundingSphere	m_tCollisionSphere_Item;
	LPD3DXMESH      m_pMesh;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
	void SetAnimationIndexBlend(int nIndex);

public:
	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere_Item; }
};