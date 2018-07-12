#include "stdafx.h"
#include "MonsterManager.h"
#include "Monster.h"



MonsterManager::MonsterManager()
{
}


MonsterManager::~MonsterManager()
{
	m_vecMonster.clear();
}

void MonsterManager::Init()
{

	MonsterSetup("zealot.X", D3DXVECTOR3(16, 0, 0), D3DXVECTOR3(0, 0, 1));
	MonsterSetup("zealot.X", D3DXVECTOR3(4, 0, 0), D3DXVECTOR3(0, 0, 1));
	MonsterSetup("zealot.X", D3DXVECTOR3(12, 0, -99), D3DXVECTOR3(0, 0, 1));
	MonsterSetup("zealot.X", D3DXVECTOR3(19, 0, -15), D3DXVECTOR3(0, 0, 1));
	//MonsterSetup("SteveJobs.X", D3DXVECTOR3(11, 0, 10), D3DXVECTOR3(0, 0, 1));
}

void MonsterManager::Update()
{
	for (m_iterMonster = m_vecMonster.begin(); m_iterMonster != m_vecMonster.end(); m_iterMonster++)
	{
		(*m_iterMonster)->Update();
	}


}

void MonsterManager::Render()
{
	for (m_iterMonster = m_vecMonster.begin(); m_iterMonster != m_vecMonster.end(); m_iterMonster++)
	{
		(*m_iterMonster)->Render();
	}
}

void MonsterManager::MonsterSetup(char * fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	Monster* m_pMonster = new Monster;
	m_pMonster->Init(fileName, pos, rot);
	m_vecMonster.push_back(m_pMonster);


}

