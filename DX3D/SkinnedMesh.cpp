#include "stdafx.h"
#include "SkinnedMesh.h"
#include "AllocateHierarchy.h"


SkinnedMesh::SkinnedMesh()
	: m_pRoot(NULL)
	, m_pAnimationController(NULL)
	, m_fPassedBlendTime(0.0f)
	, m_fBlendTime(0.5f)
	, m_isBlend(false)
	, m_pAniSet(NULL)

{
	ZeroMemory(&m_stTrackDesc, sizeof(D3DXTRACK_DESC));
}

SkinnedMesh::~SkinnedMesh()
{
	AllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SAFE_RELEASE(m_pAnimationController);
	SAFE_RELEASE(m_pAniSet);
}

void SkinnedMesh::Setup(IN char * szFolder, IN char * szFile)
{
	std::string sFullPath(szFolder);
	sFullPath = sFullPath + std::string("/") + std::string(szFile);

	AllocateHierarchy ah;
	ah.SetFolder(std::string(szFolder));

	D3DXLoadMeshHierarchyFromX(sFullPath.c_str(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		g_pDevice,
		&ah,
		NULL,
		&m_pRoot,
		&m_pAnimationController);

	SetupBoneMatrixPtrs(m_pRoot);
}

void SkinnedMesh::Update()
{
	// animation
	float nTime = 0;
	if (m_pAnimationController)
	{
		// 애니메이션이 바뀔때마다 m_vAniPos = m_vPos 로 초기화 시켜주면 모든상황에서 적용됨
		// 충돌연산은 m_vPos를 이용하여 계산하면됨
		if (m_isBlend)
		{
			m_pAnimationController->GetTrackDesc(0, &m_stTrackDesc);
			m_pAnimationController->GetTrackAnimationSet(0, &m_pAniSet);
			nTime = m_stTrackDesc.Position / m_pAniSet->GetPeriod();
			m_fPassedBlendTime += g_pTimeManager->GetEllapsedTime();
			if (m_fPassedBlendTime >= m_fBlendTime)
			{
				m_pAnimationController->SetTrackWeight(0, 1.0f);
				m_pAnimationController->SetTrackEnable(1, false);
			}
			else
			{
				float fWeight = m_fPassedBlendTime / m_fBlendTime;
				m_pAnimationController->SetTrackWeight(0, fWeight);
				m_pAnimationController->SetTrackWeight(1, 1.0f - fWeight);
			}
		}

		//이것을 주석처리하고 돌리면 캐릭터가 문워크로 이동하는걸 볼 수 있다.

		//예솔이네는 업데이트에 bool값 인자를 넣고 if(!loop)일때
		//밑에 AdvanceTime을 돌리게 한걸 봤었다고 한다.
		//		if(!jump)
		//			m_pAnimationController->AdvanceTime(
		//				g_pTimeManager->GetEllapsedTime(), NULL);
		//
		//		else if (jump)
		//		{
		////			m_pAnimationController->SetTrackEnable(1, false);
		//			m_pAnimationController->AdvanceTime(
		//				0.08, NULL);
		//		}
		//if (nTime <= 0.9f)
		//{
		m_pAnimationController->AdvanceTime(
			g_pTimeManager->GetEllapsedTime() * 1.2f, NULL);
		//}
	}

	// frame & mesh
	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void SkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	if (pParent == m_pRoot)
	{
		D3DXMATRIXA16 matInverse;
		D3DXMatrixInverse(&matInverse, 0, &pBone->TransformationMatrix);
		pBone->TransformationMatrix *= matInverse;
	}
	pBone->matCombinedTransformMatrix = pBone->TransformationMatrix;


	if (pParent)
	{
		pBone->matCombinedTransformMatrix *=
			((ST_BONE*)pParent)->matCombinedTransformMatrix;
	}

	if (pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if (pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}


}

void SkinnedMesh::Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_World)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;


	ST_BONE* pBone = (ST_BONE*)pFrame;

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->MeshData.pMesh)
		{

			D3DXMATRIXA16 matR, matWorld, matT, matS;
			D3DXMatrixIdentity(&matR);	//회전행렬초기화
			D3DXMatrixRotationY(&matR, D3DX_PI);	//리소스랑 실제 방향이 달라서 맞쳐줌
			matWorld = pBone->matCombinedTransformMatrix * matR * (*m_World);		//다 곱해주고
																					//matWorld = pBone->matCombinedTransformMatrix * matR * m_matWorld;		//다 곱해주고
			g_pDevice->SetTransform(D3DTS_WORLD, &matWorld);	//월드메트리스 적용
			for (size_t i = 0; i < pBoneMesh->vecMtl.size(); i++)
			{
				g_pDevice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pDevice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		Render(pFrame->pFrameFirstChild, m_World);
	}

	if (pFrame->pFrameSibling)
	{
		Render(pFrame->pFrameSibling, m_World);
	}
}

void SkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwBoneNum = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwBoneNum; i++)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot,
					pBoneMesh->pSkinInfo->GetBoneName(i));

				pBoneMesh->ppBoneMatrixPtrs[i] =
					&(pBone->matCombinedTransformMatrix);
			}
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void SkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	// pCurrBoneMarix = pBoneOffsetMatrix * ppBoneMatrixPtrs

	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			DWORD dwBoneNum = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwBoneNum; i++)
			{
				pBoneMesh->pCurrBoneMarixs[i] =
					pBoneMesh->pBoneOffsetMatrixs[i] *
					(*pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}

		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
			pBoneMesh->pCurrBoneMarixs, NULL, src, dest);

		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
	}

	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void SkinnedMesh::SetAnimationIndex(int nIndex)
{
	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pAnimSet = NULL;
	m_pAnimationController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pAnimSet);

	SAFE_RELEASE(pAnimSet);
}

void SkinnedMesh::SetAnimationIndexBlend(int nIndex)
{

	m_isBlend = true;
	m_fPassedBlendTime = 0.0f;

	int nMax = m_pAnimationController->GetNumAnimationSets();
	if (nIndex > nMax)	nIndex = nIndex % nMax;

	LPD3DXANIMATIONSET	pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET	pNextAnimSet = NULL;
	D3DXTRACK_DESC stTrackDesc;

	m_pAnimationController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimationController->SetTrackAnimationSet(1, pPrevAnimSet);
	m_pAnimationController->SetTrackDesc(1, &stTrackDesc);


	m_pAnimationController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimationController->SetTrackAnimationSet(0, pNextAnimSet);


	m_pAnimationController->SetTrackWeight(0, 0.0f);
	m_pAnimationController->SetTrackWeight(1, 1.0f);


	m_pAnimationController->GetAnimationSet(nIndex, &m_pAniSet);
	m_pAnimationController->SetTrackAnimationSet(0, m_pAniSet);

	m_pAnimationController->SetTrackPosition(0, 0);
	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);
}

void SkinnedMesh::FindBone(IN char * szBoneName, ST_BONE* pBone, OUT D3DXMATRIXA16 & pMatrix)
{
	if (pBone == NULL)
		pBone = (ST_BONE*)m_pRoot;

	if (pBone->Name)
	{
		if (!strcmp(pBone->Name, szBoneName))
		{
			pMatrix = pBone->matCombinedTransformMatrix;
		}
	}

	if (pBone->pFrameFirstChild)
	{
		FindBone(szBoneName, (ST_BONE*)pBone->pFrameFirstChild, pMatrix);
	}

	if (pBone->pFrameSibling)
	{
		FindBone(szBoneName, (ST_BONE*)pBone->pFrameSibling, pMatrix);
	}
}

void SkinnedMesh::Init()
{
}

void SkinnedMesh::Render()
{
}
