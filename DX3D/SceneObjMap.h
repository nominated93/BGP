#pragma once
#include "IScene.h"

class ObjMap;
class Player;
class SkyBox;
class Picking;

class ItemManager;
class Inventory;
class Collision;
class MonsterManager;

class SceneObjMap : public IScene
{
private:
	ObjMap *		m_pObjMap;
	Player *		m_pPlayer;
	SkyBox *		m_pSkyBox;
	Picking *		m_pPicking;
	ItemManager *   m_pItemManager;
	Inventory *     m_pInventory;
	
	Collision*		m_pCollision;
	MonsterManager*	m_pMonsterManager;

public:
	SceneObjMap();
	~SceneObjMap();

	// IScene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
};

