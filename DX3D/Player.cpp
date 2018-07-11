#include "stdafx.h"
#include "Player.h"
#include "UIImage.h"
#include "SkinnedMesh.h"
#include "BulletManager.h"



Player::Player():
	m_pSkinnedMesh(NULL),
	m_pBM(NULL), 
	m_pCrossImg(NULL)
{
}


Player::~Player()
{
	SAFE_RELEASE(m_pSkinnedMesh);
	SAFE_RELEASE(m_pBM);
	SAFE_RELEASE(m_pCrossImg);
}

void Player::Init()
{
	m_pos = D3DXVECTOR3(50, 0, 0);

	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	m_pSkinnedMesh = new SkinnedMesh();
	m_pSkinnedMesh->Setup("../../", "Character.X");

	//m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("주인공");
	//m_pSkinnedMesh->SetAnimationIndex(83);
	//m_szCurrentFile = "주인공";

	//crosshair
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pCrossImg = new UIImage(m_pSprite);
	m_pCrossImg->SetTexture("resources/images/crosshair_g.png");	
	m_pCrossImg->SetPosition(&D3DXVECTOR3(rc.right/2-10, rc.bottom/2, 0));
	m_pCrossImg->Update();

	//볼렛
	m_pBM = new BulletManager(); m_pBM->Init();
	
	//아이템충돌 구 생성
	m_tCollisionSphere_Item.center = m_pos;
	m_tCollisionSphere_Item.center = D3DXVECTOR3(0,0,0);
	m_tCollisionSphere_Item.radius = 20;
	D3DXCreateSphere(g_pDevice, m_tCollisionSphere_Item.radius, 10, 10, &m_pMesh, NULL);
}

void Player::Update()
{
	IUnitObject::UpdateKeyboardState();
	m_rot.y = g_pCamera->m_rotY;
	IUnitObject::UpdatePosition();
	
	//if (GetKeyState('W') & 0x8000)
	//{
	//	//m_eState = Melee_stand_run_front;
	//	m_pSkinnedMesh->SetAnimationIndexBlend(76);//무기없이 뛰어서 앞으로
	//}

	m_pSkinnedMesh->Update();

	m_tCollisionSphere_Item.center = m_pos;

	//총쏘기
	if (g_pKeyboardManager->isStayKeyDown(VK_LBUTTON))
	{
		m_pBM->Fire(&m_pos, &(g_pCamera->m_forward));
	}
	

	m_pBM->Update();


}

void Player::Render()
{
	
	D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld;

	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	//D3DXMatrixRotationX(&matRX, -D3DX_PI / 2);
	D3DXMatrixRotationY(&matRY, m_rot.y);
	//D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	matWorld = matS * matRY * matT;
	
	m_pSkinnedMesh->Render(NULL, &matWorld);

	m_pCrossImg->Render();

	m_pMesh->DrawSubset(0);
	//m_pSkinnedMesh->Render(NULL, &g_pCamera->m_matView); //1인칭
	//m_pSkinnedMesh->Render(NULL, &m_matWorld);

	m_pBM->Render();

}

void Player::SetAnimationIndexBlend(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
}

