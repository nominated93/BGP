#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Player.h"
#include "EnemyManager.h"
#include "OBB.h"
#include "IMap.h"

BulletManager::BulletManager()
	: m_pPlayer(NULL),
	m_pEnemyManager(NULL)
{
}


BulletManager::~BulletManager()
{
	m_vecBullet.clear();
}

void BulletManager::Init()
{
}

void BulletManager::Update()
{

	for (m_iterBullet = m_vecBullet.begin(); m_iterBullet != m_vecBullet.end(); m_iterBullet++)
	{


		tempPos = (*m_iterBullet)->GetPosition() + 0.15 * (*m_iterBullet)->GetRotation();

		OBB tempOBB;
		tempOBB.Init(tempPos, (*m_iterBullet)->GetPosition());

		OBB tempOBB2;
		tempOBB2.Init(m_pPlayer->GetPosition(), m_pPlayer->GetPosition());
		//D3DXMATRIXA16 tempMat;
		//D3DXMatrixIdentity(&tempMat);
		//tempOBB.Update(&tempMat);

		if (m_pPlayer)
		{
			if (OBB::IsCollision(&tempOBB2, &tempOBB))
			{
				m_pPlayer->SetPosition(&(m_pPlayer->GetPosition() + D3DXVECTOR3(0.02f, 0.02f, 0)));
				//m_pPlayer->SetCurrHP(50);
				m_pPlayer->BulletHit();

				//Remove();
			}
		}
		//if (m_pEnemyManager)
		//{
		//	if (OBB::IsCollision(&tempOBB2, &tempOBB))
		//	{
		//		m_pEnemyManager->SetPosition(&(m_pPlayer->GetPosition() + D3DXVECTOR3(0.02f, 0.02f, 0)));
		//		//m_pPlayer->SetCurrHP(50);
		//		m_pEnemyManager->BulletHit();

		//		//Remove();
		//	}
		//}

		(*m_iterBullet)->Update();
	}


	Remove();
}

void BulletManager::Render()
{
	for (m_iterBullet = m_vecBullet.begin(); m_iterBullet != m_vecBullet.end(); m_iterBullet++)
	{
		(*m_iterBullet)->Render();
	}
}

void BulletManager::Fire(D3DXVECTOR3* pos, D3DXVECTOR3* dir)
{
	Bullet* bullet;
	bullet = new Bullet;
	bullet->Setup(pos, dir);

	m_vecBullet.push_back(bullet);
}

void BulletManager::Fire(float damage, float speed, float range, D3DXVECTOR3 pos, D3DXVECTOR3 dir)
{
	for (int i = 0; i < BULLETMAX; i++)
	{
		//if (m_vecBullet[i].GetisAlive() == true) continue;
		//m_vecBullet[i].Setup(damage, speed, range, pos, dir);
		break;
	}
}

void BulletManager::Setup(Player * player, EnemyManager * enemyManager, IMap * map)
{
	m_pPlayer = player;
	m_pEnemyManager = enemyManager;
	m_pObjMap = map;
}

void BulletManager::Remove()
{
	float fRange = 150.f;
	for (m_iterBullet = m_vecBullet.begin(); m_iterBullet != m_vecBullet.end(); )
	{
		D3DXVECTOR3 vDiff = (*m_iterBullet)->GetStartPosition() - (*m_iterBullet)->GetPosition();
		float fDistance = D3DXVec3Length(&vDiff);

		if (fDistance >= fRange)
		{
			m_iterBullet = m_vecBullet.erase(m_iterBullet);
		}
		else
			m_iterBullet++;
	}
}