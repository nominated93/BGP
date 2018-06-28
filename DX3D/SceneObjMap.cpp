#include "stdafx.h"
#include "SceneObjMap.h"
#include "ObjMap.h"
#include "AseCharacter.h"
#include "Player.h"
#include "SkyBox.h"
#include "Picking.h"
#include "Bullet.h"
#include "BulletManager.h"
#include "Inventory.h"
#include "ItemManager.h"
#include "Item.h"
#include "Collision.h"


SceneObjMap::SceneObjMap()
{
	m_pSkyBox = NULL;
	m_pObjMap = NULL;
	m_pPlayer = NULL;
	m_pPicking = NULL;
	m_pCollision = NULL;
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
		"resources/skybox/sahara_bk.tga"); AddSimpleDisplayObj(m_pSkyBox);
	m_pObjMap = new ObjMap; m_pObjMap->Init(); AddSimpleDisplayObj(m_pObjMap);
	m_pPlayer = new Player; m_pPlayer->Init();  AddSimpleDisplayObj(m_pPlayer);
	m_pPicking = new Picking; m_pPicking->Init(); AddSimpleDisplayObj(m_pPicking);
	m_pBulletManager = new BulletManager; m_pBulletManager->Init(); AddSimpleDisplayObj(m_pBulletManager);
	m_pItemManager = new ItemManager; m_pItemManager->Init(); AddSimpleDisplayObj(m_pItemManager);
	m_pInventory = new Inventory; m_pInventory->Init(); AddSimpleDisplayObj(m_pInventory);
	m_pCollision = new Collision; m_pCollision->Init(m_pPlayer, m_pBulletManager, m_pItemManager, m_pInventory); AddSimpleDisplayObj(m_pCollision);


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

