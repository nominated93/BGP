#include "stdafx.h"
#include "Collision.h"
#include "Player.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Item.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::Init()
{
}

void Collision::Init(Player * pPlayer, BulletManager * pBM, ItemManager * pIM, Inventory * pInven)
{
	m_pPlayer = pPlayer;
	m_pBM = pBM;
	m_pIM = pIM;
	m_pInven = pInven;

}

void Collision::Update()
{
	Collision_ItemPlayer();
}

void Collision::Render()
{
}

bool Collision::CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2)
{
	float fDistance;
	D3DXVECTOR3 vDiff;
	vDiff = (vCenter2 / 0.05f) - (vCenter1 / 0.05f);   //리소스 크기를 0.05만큼 줄여줘서 계산법에서 나눈다
	fDistance = D3DXVec3Length(&vDiff);
	if (fDistance <= (fRadius1 + fRadius2))
		return true;

	return false;
}

void Collision::Collision_ItemPlayer()
{
	vector<Item*>* pVecItem = m_pIM->GetPVecItem();
	vector<Item*>::iterator iterItem;

	for (iterItem = pVecItem->begin(); iterItem != pVecItem->end();)
	{
		if (CheckSphereIntersect((*iterItem)->GetCollisionSphere().center, (*iterItem)->GetCollisionSphere().radius,
			m_pPlayer->GetCollisionSphere().center, m_pPlayer->GetCollisionSphere().radius))
		{
			(*iterItem)->SetIsCollision(true);

			if (g_pKeyManager->isOnceKeyDown('F'))
			{
				m_pInven->AddItemToInven((*iterItem)->GetItemName());
				iterItem = (*pVecItem).erase(iterItem);
			}
			else
				iterItem++;
		}

		else
		{
			(*iterItem)->SetIsCollision(false);
			iterItem++;
		}
	}
}