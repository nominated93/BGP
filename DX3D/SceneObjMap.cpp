#include "stdafx.h"
#include "SceneObjMap.h"
#include "ObjMap.h"
#include "Player.h"
#include "SkyBox.h"
#include "Picking.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Collision.h"
#include "BulletManager.h"
#include "MonsterManager.h"
#include "EnemyManager.h"
#include "OBB.h"
#include "Minimap.h"

SceneObjMap::SceneObjMap()
{
	m_pSkyBox = NULL;
	m_pObjMap = NULL;
	m_pMinimap = NULL;
	m_pPlayer = NULL;
	m_pPicking = NULL;
	m_pInventory = NULL;
	m_pCollision = NULL;
	m_pMonsterManager = NULL;
	m_pEnemyManager = NULL;
}


SceneObjMap::~SceneObjMap()
{
	OnDestructIScene();
}

void SceneObjMap::Init()
{

	m_pSkyBox = new SkyBox("resources/skybox/sahara_up.tga",
		"resources/skybox/sahara_dn.tga",
		"resources/skybox/sahara_lf.tga",
		"resources/skybox/sahara_rt.tga",
		"resources/skybox/sahara_ft.tga",
		"resources/skybox/sahara_bk.tga");



	g_pSkinnedMeshManager->Load("PlayerAction", "../../", "action.X");
	g_pSkinnedMeshManager->Load("Action", "../../", "action.X");
	g_pSkinnedMeshManager->Load("Character", "../../", "Character.X");
	g_pMeshManager->AddMesh("AK-47", "resources/weapons", "AK-47.X"); //AK-47 추가

	m_pObjMap = new ObjMap; m_pObjMap->Init(); AddSimpleDisplayObj(m_pObjMap);
	m_pPlayer = new Player; m_pPlayer->Init();  AddSimpleDisplayObj(m_pPlayer);
	m_pEnemyManager = new EnemyManager; m_pEnemyManager->Init(); AddSimpleDisplayObj(m_pEnemyManager);
	m_pBulletManager = new BulletManager; m_pBulletManager->Setup(m_pPlayer, m_pEnemyManager, m_pObjMap); AddSimpleDisplayObj(m_pBulletManager);
	//m_pMonsterManager = new MonsterManager; m_pMonsterManager->Init(); AddSimpleDisplayObj(m_pMonsterManager);
	m_pPicking = new Picking; m_pPicking->Init(); AddSimpleDisplayObj(m_pPicking);

	m_pMinimap = new Minimap; m_pMinimap->Init(); AddSimpleDisplayObj(m_pMinimap);

	m_pItemManager = new ItemManager; m_pItemManager->Init(); AddSimpleDisplayObj(m_pItemManager);
	m_pInventory = new Inventory; m_pInventory->Init(); AddSimpleDisplayObj(m_pInventory);

	//Collision Init이 제일 뒤에 있어야됨
	m_pCollision = new Collision; m_pCollision->Init(m_pPlayer, m_pPlayer->GetPBulletManager(), m_pItemManager, m_pInventory); AddSimpleDisplayObj(m_pCollision);

	//test
	m_pPlayer->Init(m_pBulletManager);

	m_pEnemyManager->Init(m_pPlayer, m_pBulletManager, m_pObjMap);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(16, -60, 0), D3DXVECTOR3(0, 0, 1), 0);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(4, -60, 0), D3DXVECTOR3(0.8, 0, 0.6), 1);
	m_pEnemyManager->makeEnemy(D3DXVECTOR3(12, -60, -99), D3DXVECTOR3(-0.07, 0, 0.99), 2);

	D3DXVECTOR3 dir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&dir, &dir);
	D3DLIGHT9 light = DXUtil::InitDirectional(&dir, &WHITE);
	g_pDevice->SetLight(0, &light);
	g_pDevice->LightEnable(0, true);

	g_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}

void SceneObjMap::Update()
{
	OnUpdateIScene();
}

void SceneObjMap::Render()
{
	OnRenderIScene();
}

void SceneObjMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	SAFE_WNDPROC(m_pPicking);
}
