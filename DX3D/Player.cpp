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

	//m_pSkinnedMesh = new SkinnedMesh();
	//m_pSkinnedMesh->Setup("../../", "Character.X");

	g_pSkinnedMeshManager->Load("Player", "../../", "Character.X");
	g_pMeshManager->AddMesh("AK-47", "resources/weapons", "AK-47.X"); //AK-47 추가

	m_pSkinnedMesh = g_pSkinnedMeshManager->GetSkinnedMesh("Player");
	m_pSkinnedMesh->SetAnimationIndex(83-45);
	//m_pSkinnedMesh->SetAnimationIndex(83);

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

	m_pSkinnedMesh->Update();

	m_tCollisionSphere_Item.center = m_pos;

	//총쏘기
	if (g_pKeyboardManager->isStayKeyDown(VK_LBUTTON))
	{
		m_pBM->Fire(&m_pos, &(g_pCamera->m_forward));
	}
	
	m_pBM->Update();

	//위치
	Debug->AddText("pos : ");
	Debug->AddText(m_pos);
	Debug->EndLine();

}

void Player::Render()
{
	
	D3DXMATRIXA16 matS, matR, matRY, matT, matWorld, matBone;
	D3DXMatrixScaling(&matS, 0.04f, 0.04f, 0.04f);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixRotationY(&matR, D3DX_PI);
	D3DXMatrixRotationY(&matRY, m_rot.y);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = matS  * matRY * matT;

	g_pSkinnedMeshManager->GetBoneMatrix("Player", "hand_r", matBone);
	matWorld = matBone * matR *m_matWorld;

	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pMeshManager->Render("AK-47");

	m_pSkinnedMesh->Render(NULL, &m_matWorld);

	m_pCrossImg->Render();

	m_pMesh->DrawSubset(0);

	m_pBM->Render();
} 

void Player::SetAnimationIndexBlend(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
}

