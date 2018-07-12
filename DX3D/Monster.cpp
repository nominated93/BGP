#include "stdafx.h"
#include "Monster.h"
#include "SkinnedMesh.h"



Monster::Monster()
	:m_pSkinnedMesh(NULL)
{
}


Monster::~Monster()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void Monster::Init()
{


}


void Monster::Init(char* fileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{




	m_pSkinnedMesh = new SkinnedMesh();
	m_pSkinnedMesh->SetPosition(&D3DXVECTOR3(900, 0, 0));
	m_pos = pos;
	m_rot = rot;
	m_pSkinnedMesh->Setup("../../", fileName);


}
void Monster::Update()
{
	m_pSkinnedMesh->Update();


}

void Monster::Render()
{

	D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld;

	D3DXMatrixScaling(&matS, 7.0f, 7.0f, 7.0f);
	D3DXMatrixRotationX(&matRX, D3DX_PI / 2);
	D3DXMatrixRotationY(&matRY, D3DX_PI / 2);
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y - 60, m_pos.z);

	matWorld = matS * matRX * matRY*matT;


	m_pSkinnedMesh->Render(NULL, &matWorld);
	//m_pSkinnedMesh->Render(NULL, &g_pCamera->m_matView); //1ÀÎÄª



}
void Monster::SetAnimationIndexBlend(int nIndex)
{
	m_pSkinnedMesh->SetAnimationIndexBlend(nIndex);
}

