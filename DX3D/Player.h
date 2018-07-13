#pragma once
#include "IUnitObject.h"
#include "ProgressBarManager.h"

class SkinnedMesh;
class UIImage;
class BulletManager;

enum eAniDirection {
	Front = 4, Left_front, Left, Left_back, Back, Right_back, Right, Right_front
};

//enum eAniPunch {
//
//};

class Player : public IUnitObject
{

private:
	SkinnedMesh*			m_pSkinnedMesh;
	UIImage*				m_pCrossImg;
	UIImage*				m_pZoomin;
	UIImage*				m_pAk47Img;
	BoundingSphere			m_tCollisionSphere_Item;
	LPD3DXMESH				m_pMesh;
	string					m_szCurrentFile;
	ePlayerState			m_eState;
	LPD3DXSPRITE			m_pSprite;
	BulletManager*			m_pBM;
	ProgressBarManager*		m_pPB;

	//D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld, matBone;

	bool m_isZoom;

	// 애니메이션
	int curAniIndex;
	int nextAniIndex;
	int baseAniIndex;
	int walkAniIndex;

private:
	float m_fCurrHP;
	float m_fMaxHP;


public:
	Player();
	~Player();

	void Init();
	void Update();
	void Render();
	void SetAnimationIndexBlend(int nIndex);

	// 애니메이션
	void AnimationConversion();

public:
	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere_Item; }
	BulletManager* GetPBulletManager() { return m_pBM; }
};