#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet() :
	m_fSpeed(5.f),
	m_isFire(false)
{
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
}

void Bullet::Setup(D3DXVECTOR3* pos, D3DXVECTOR3* dir)
{
	m_pos = *pos;
	m_rot = *dir;
	m_pos.y += 3.0f;
	m_vStartPos = m_pos;

	float radius = 0.2f;
	D3DXCreateSphere(g_pDevice, radius, 10, 10, &m_pSphere, NULL);
}

void Bullet::Update()
{
}

void Bullet::Render()
{
	D3DXMATRIXA16 matS, matR, matT, matWorld;


	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	Move();
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);

	matWorld = matS * matR * matT;

	g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pDevice->SetTexture(0, NULL);
	m_pSphere->DrawSubset(0);
}

void Bullet::Move()
{
	//D3DXVECTOR3 v(0, 0, 1);
	//m_pos = m_pos + (m_rot * m_fSpeed);
	m_pos = m_pos + (m_rot * m_fSpeed);
}




