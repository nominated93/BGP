#pragma once
#include "IScene.h"

class ObjMap;
class AseCharacter;
class Player;
class SkyBox;
class Picking;

class BulletManager;
class ItemManager;
class Inventory;

class SceneObjMap : public IScene
{
private:
	ObjMap *		m_pObjMap;
	AseCharacter *	m_pAseCharacter;
	Player *		m_pPlayer;
	SkyBox *		m_pSkyBox;
	Picking *		m_pPicking;
	BulletManager *	m_pBulletManager;
	ItemManager *   m_pItemManager;
	Inventory *     m_pInventory;

public:
	SceneObjMap();
	~SceneObjMap();

	bool CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2);
	void CollisionItem();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

