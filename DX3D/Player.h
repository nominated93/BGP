#pragma once
#include "IUnitObject.h"

class SkinnedMesh;
class UIImage;
class BulletManager;

class Player : public IUnitObject
{

private:
	SkinnedMesh*	m_pSkinnedMesh;
	UIImage*		m_pCrossImg;
	BoundingSphere	m_tCollisionSphere_Item;
	LPD3DXMESH      m_pMesh;
	string			m_szCurrentFile;
	ePlayerState	m_eState;
	LPD3DXSPRITE	m_pSprite;
	BulletManager*	m_pBM;

	D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld, matBone;

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
	void SetAnimationIndexBlend(int nIndex);

public:
	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere_Item; }
	BulletManager* GetPBulletManager() { return m_pBM; }
};