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


SceneObjMap::SceneObjMap()
{
	m_pSkyBox = NULL;
	m_pObjMap = NULL;
	m_pPlayer = NULL;
	m_pPicking = NULL;
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
	m_pObjMap = new ObjMap; m_pObjMap->Init(); AddSimpleDisplayObj(m_pObjMap);
	m_pPlayer = new Player; m_pPlayer->Init();  AddSimpleDisplayObj(m_pPlayer);
	m_pPicking = new Picking; m_pPicking->Init(); AddSimpleDisplayObj(m_pPicking);

	/*인벤토리 시작*/
	m_pBulletManager = new BulletManager; m_pBulletManager->Init(); AddSimpleDisplayObj(m_pBulletManager);
	m_pItemManager = new ItemManager; m_pItemManager->Init(); AddSimpleDisplayObj(m_pItemManager);
	m_pInventory = new Inventory; m_pInventory->Init(); AddSimpleDisplayObj(m_pInventory);

	//아이템셋팅
	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(10, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(6, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(-5, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR);

	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(12, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(8, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(-3, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR);

	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(12, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(8, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(-3, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR);

	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(15, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(15, 1, 6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(15, 1, 3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR);

	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(3, 1, 0), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("AK-47.X", D3DXVECTOR3(15, 1, -6), D3DXVECTOR3(0, 0, 1), ITEM_LIST::AK47);
	m_pItemManager->ItemSetup("F_Armor_C_01.X", D3DXVECTOR3(15, 1, -3), D3DXVECTOR3(0, 0, 1), ITEM_LIST::ARMOR);
	/*인벤토리 끝*/

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
	CollisionItem();
}

void SceneObjMap::Render()
{
	m_pSkyBox->Render();
	OnRenderIScene();
}

void SceneObjMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
	SAFE_WNDPROC(m_pPicking);
}

bool SceneObjMap::CheckSphereIntersect(D3DXVECTOR3 vCenter1, float fRadius1, D3DXVECTOR3 vCenter2, float fRadius2)
{
	float fDistance;
	D3DXVECTOR3 vDiff;
	vDiff = (vCenter2 / 0.05f) - (vCenter1 / 0.05f);   //리소스 크기를 0.05만큼 줄여줘서 계산법에서도 줄여준다
	fDistance = D3DXVec3Length(&vDiff);
	if (fDistance <= (fRadius1 + fRadius2))
		return true;

	return false;
}

void SceneObjMap::CollisionItem()
{
	vector<Item*>* pVecItem = m_pItemManager->GetPVecItem();
	vector<Item*>::iterator iterItem;

	for (iterItem = pVecItem->begin(); iterItem != pVecItem->end();)
	{
		if (CheckSphereIntersect((*iterItem)->GetCollisionSphere().center, (*iterItem)->GetCollisionSphere().radius,
			m_pPlayer->GetCollisionSphere().center, m_pPlayer->GetCollisionSphere().radius))
		{
			bool check = false;
			(*iterItem)->SetIsCollision(true);

			if (GetKeyState('F') & 0x08000)
			{
				m_pInventory->AddItemToInven((*iterItem)->GetItemList());
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