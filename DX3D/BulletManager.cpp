#include "stdafx.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "Camera.h"


BulletManager::BulletManager()
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

void BulletManager::Remove()
{
	float fRange = 50.f;
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