#pragma once
#define MAXENEMY 20

class Enemy;
class Player;
class BulletManager;
class Frustum;
class IMap;

class EnemyManager : public IUnitObject
{
private:
	std::string m_sEnemyName[20];
	SYNTHESIZE_REF(std::vector<Enemy*>, m_vecEnemy, vecEnemy);

public:
	EnemyManager();
	~EnemyManager();

	void makeEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 dir, int patternNum);
	void Init(Player* player, BulletManager* bulletsManager, IMap* map);
	void Update();
	void Render();

	// Inherited via IUnitObject
	virtual void Init() override;
};
