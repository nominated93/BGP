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
class Collision;
class Equipment;

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
	Equipment*		m_pEquipment;
	
	Collision*		m_pCollision;

public:
	SceneObjMap();
	~SceneObjMap();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

