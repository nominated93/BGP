#include "stdafx.h"
#include "Player.h"

#include "SkinnedMesh.h"



Player::Player()
	:m_pSkinnedMesh(NULL)
{
}


Player::~Player()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void Player::Init()
{
	g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);


	m_pSkinnedMesh = new SkinnedMesh();
	m_pSkinnedMesh->Setup("resources/player", "player.X");


	//아이템충돌 구 생성
	m_tCollisionSphere_Item.center = m_pos;
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
}

void Player::Render()
{

	D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld;

	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	//D3DXMatrixRotationX(&matRX, -D3DX_PI / 2);
	D3DXMatrixRotationY(&matRY, m_rot.y);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	matWorld = matS * matRY * matT;
	

	m_pSkinnedMesh->Render(NULL, &matWorld);

	m_pMesh->DrawSubset(0);

	//m_pSkinnedMesh->Render(NULL, &g_pCamera->m_matView); //1인칭
	//m_pSkinnedMesh->Render(NULL, &m_matWorld);

}

void Player::SetAnimationIndexBlend(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
}