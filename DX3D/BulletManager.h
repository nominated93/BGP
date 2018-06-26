#pragma once
#include "IDisplayObject.h"

class Bullet;

class BulletManager : public IDisplayObject
{
	vector<Bullet*> m_vecBullet;
	vector<Bullet*>::iterator m_iterBullet;

public:
	BulletManager();
	~BulletManager();

	void Init();
	void Update();
	void Render();

	void Fire(D3DXVECTOR3* pos, D3DXVECTOR3* dir);
	void Remove();
};

