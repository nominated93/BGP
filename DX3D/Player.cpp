#include "stdafx.h"
#include "Player.h"
#include "UIImage.h"
#include "SkinnedMesh.h"
#include "BulletManager.h"


Player::Player():
	m_pSkinnedMesh(NULL),
	m_pBM(NULL), 
	m_pCrossImg(NULL),
	m_pPB(NULL),
	m_isZoom(false)
{
}

Player::~Player()
{
	SAFE_RELEASE(m_pSkinnedMesh);
	SAFE_RELEASE(m_pBM);
	SAFE_RELEASE(m_pCrossImg);
	SAFE_RELEASE(m_pPB);
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

	// 애니메이션 셋팅 기본 서있는 아이들
	walkAniIndex = 0;
	curAniIndex = baseAniIndex = Rifle_stand_idle;
	m_pSkinnedMesh->SetAnimationIndex(curAniIndex);

	//crosshair
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_pCrossImg = new UIImage(m_pSprite);
	m_pCrossImg->SetTexture("resources/images/crosshair_g.png");	
	m_pCrossImg->SetPosition(&D3DXVECTOR3(rc.right/2-10, rc.bottom/2, 0));
	m_pCrossImg->Update();

	m_pZoomin = new UIImage(m_pSprite);
	m_pZoomin->SetTexture("resources/weapons/zoom_in.png");
	m_pZoomin->SetPosition(&D3DXVECTOR3(rc.right / 2 - m_pZoomin->GetInfo().Width / 2 , rc.bottom / 2 - m_pZoomin->GetInfo().Height / 2, 0));
	m_pZoomin->Update();

	//볼렛
	//m_pBM = new BulletManager(); m_pBM->Init();
	
	m_pAk47Img = new UIImage(m_pSprite);
	m_pAk47Img->SetTexture("resources/UI/ak-47_back.png");
	m_pAk47Img->SetPosition(&D3DXVECTOR3(rc.right / 2 - m_pAk47Img->GetInfo().Width / 2, WINSIZEY - WINSIZEY / 6, 0));
	m_pAk47Img->Update();

	//체력바
	m_fMaxHP = m_fCurrHP = 100.f;
	m_pPB = new ProgressBarManager; m_pPB->Init();
	m_pPB->SetPosition(WINSIZEX / 2 - m_pPB->GetPUIImg()->GetInfo().Width / 2, WINSIZEY - WINSIZEY / 15);
	m_pPB->SetGauge(m_fCurrHP, m_fMaxHP);

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


	AnimationConversion();
	m_pSkinnedMesh->Update();

	m_tCollisionSphere_Item.center = m_pos;

	//총쏘기
	if (g_pKeyboardManager->isStayKeyDown(VK_LBUTTON))
	{
		//m_pBM->Fire(&m_pos, &(g_pCamera->m_forward));
	}
	//m_pBM->Update();

	if (m_isZoom == false)
	{
		if (g_pKeyboardManager->isOnceKeyDown(VK_RBUTTON))
		{
			m_isZoom = true;
			m_pZoomin->Update();
			g_pCamera->SetDistance(-30.0f);
		}
	}
	else
	{
		if (g_pKeyboardManager->isOnceKeyDown(VK_RBUTTON) || g_pKeyboardManager->isOnceKeyDown(VK_LBUTTON))
		{
			m_isZoom = false;
			m_pZoomin->Update();
			g_pCamera->SetDistance(5.0f);
		}
	}

	//체력바

	if (g_pKeyboardManager->isStayKeyDown('1'))
	{
		m_fCurrHP -= 0.5f;	
	}
	if (g_pKeyboardManager->isStayKeyDown('2'))
	{
		m_fCurrHP += 0.5f;
	}
	if (m_fCurrHP == 100)
	{
		m_pPB->SetAlphaValue(80);
	}
	else
	{
		m_pPB->SetAlphaValue(50);
	}
	m_pPB->Update();
	m_pPB->SetGauge(m_fCurrHP, m_fMaxHP);

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

	
	if (m_isZoom)
	{
		m_pZoomin->Render();
	}
	else 
	{
		m_pCrossImg->Render();
	}

	//m_pMesh->DrawSubset(0);

	//m_pBM->Render();

	//체력바
	m_pAk47Img->Render();
	m_pPB->Render();
	Debug->AddText("HP : ");
	Debug->AddText(m_fCurrHP);
	Debug->EndLine();
} 

void Player::SetAnimationIndexBlend(int nIndex)
{
	if (curAniIndex != nIndex)
	{
		m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
		curAniIndex = nIndex;
	}
}

void Player::AnimationConversion()
{
	m_moveSpeed = 0.15;

	// 애니메이션 셋팅
	if (m_keyState.bSit)	// 앉아있냐 아니냐
	{
		m_moveSpeed = 0.09;
		baseAniIndex = Rifle_crouch_idle;
	}
	else
		baseAniIndex = Rifle_stand_idle;


	nextAniIndex = baseAniIndex;

	if (m_keyState.bWalk && !m_keyState.bSit)
	{
		m_moveSpeed = 0.09;
		walkAniIndex = 9;
	}
	else
		walkAniIndex = 0;

	if (m_keyState.deltaPos.x < 0)
		nextAniIndex = baseAniIndex - walkAniIndex - Left;
	else if (m_keyState.deltaPos.x > 0)
		nextAniIndex = baseAniIndex - walkAniIndex - Right;

	if (m_keyState.deltaPos.z > 0)
		nextAniIndex = baseAniIndex - walkAniIndex - Front;
	else if (m_keyState.deltaPos.z < 0)
		nextAniIndex = baseAniIndex - walkAniIndex - Back;


	SetAnimationIndexBlend(nextAniIndex);
}