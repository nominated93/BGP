#pragma once

#include "IDisplayObject.h"

class Player;
class BulletManager;
class ItemManager;
class Inventory;
class Collision :public IDisplayObject
{
private:
	Player *		m_pPlayer;
	BulletManager*	m_pBM;
	ItemManager*	m_pIM;
	Inventory*		m_pInven;

public:
	Collision();
	~Collision();

public:
	void Init();
	void Init(Player * pPlayer, BulletManager* pBM, ItemManager* pIM, Inventory* pInven);
	void Update();
	void Render();
	bool CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2);
	void Collision_ItemPlayer();
};

