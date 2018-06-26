#include "stdafx.h"
#include "AseCharacter.h"
#include "AseObject.h"
#include "AseLoader.h"

AseCharacter::AseCharacter()
{
	m_pCurrObj = NULL;
	m_pStandObj = NULL;
	m_pRunObj = NULL;
	m_baseRotY = D3DX_PI;

	m_forward.x = 1;
	m_pos = D3DXVECTOR3(5, 5, 5);
}


AseCharacter::~AseCharacter()
{
	//m_pCurrObj->ReleaseAll();
	m_pStandObj->ReleaseAll();
	m_pRunObj->ReleaseAll();
}

void AseCharacter::Init()
{
	//g_pObjMgr->AddToTagList(TAG_PLAYER, this);
	g_pCamera->SetTarget(&m_pos);
	g_pKeyboardManager->SetMovingTarget(&m_keyState);

	Load(m_pStandObj, "resources/ase/woman_01_all_stand_fixed.ASE");
	m_pStandObj->Init();

	Load(m_pRunObj, "resources/ase/woman_01_all.ASE");
	m_pRunObj->Init();

	SetCurrentObject(m_pStandObj);
}

void AseCharacter::Update()
{
	//IUnitObject::UpdatePosition();
	IUnitObject::UpdateKeyboardState();
	IUnitObject::UpdatePositionToDestination();

	if (m_isMoving == true)
	{
		if (m_pCurrObj != m_pRunObj)
			SetCurrentObject(m_pRunObj);
	}
	else
	{
		if (m_pCurrObj != m_pStandObj)
			SetCurrentObject(m_pStandObj);
	}

	int firstTick = m_aseScene.numFirstFrame * m_aseScene.ticksPerFrame;
	int lastTick = m_aseScene.numLastFrame * m_aseScene.ticksPerFrame;
	int tickSpeed = m_aseScene.frameSpeed * m_aseScene.ticksPerFrame;
	DWORD tickCount = ((int)((tickSpeed / 1000.f) * GetTickCount()) % (lastTick - firstTick) + firstTick);

	if (m_pCurrObj != NULL)
		m_pCurrObj->Update(tickCount, &m_matWorld);

	Debug->AddText("Pos : ");
	Debug->AddText(m_pos);
	Debug->EndLine();
}

void AseCharacter::Render()
{
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true); //�����ϰ�
	g_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);

	g_pDevice->SetRenderState(D3DRS_BLENDFACTOR, 0xffff22cc);
	
	/*
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	*/

	g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	SAFE_RENDER(m_pCurrObj);

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void AseCharacter::Load(OUT AseObject *& rootObj, const char * fullPath)
{
	AseLoader loader;
	rootObj = loader.Load(fullPath, &m_aseScene);
}
