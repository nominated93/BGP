#pragma once
#include "IUnitObject.h"
#include "ProgressBarManager.h"

class SkinnedMesh;
class UIImage;
class UIText;
class BulletManager;
class OBB;

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
	UIText*					m_pBulletCurrText;
	UIText*					m_pBulletTotalText;
	int						m_bulletCurrCnt;
	int						m_bulletTotalCnt;
	BoundingSphere			m_tCollisionSphere_Item;
	LPD3DXMESH				m_pMesh;
	string					m_szCurrentFile;
	ePlayerState			m_ePlayerState;
	int						m_eState;
	LPD3DXSPRITE			m_pSprite;
	BulletManager*			m_pBM;
	ProgressBarManager*		m_pPB;
	OBB*					m_pOBB;		


	char					m_bulletCntStr[1024];
	char					m_bulletTotalStr[1024];


	//D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld, matBone;

	bool						m_isZoom;
	bool						m_isReload;

	float						aniTime;
	LPD3DXANIMATIONCONTROLLER	aniControlerTmp; 
	LPD3DXANIMATIONCONTROLLER	m_pAniController;
	LPD3DXANIMATIONSET			m_pAniSet;

	// 애니메이션
	int curAniIndex;
	int nextAniIndex;
	int baseAniIndex;
	int walkAniIndex;

	int actionIndex;

private:
	float m_fCurrHP;
	float m_fMaxHP;


public:
	Player();
	~Player();

	void Init(BulletManager * bm);

	void Init();
	void Update();
	void Render();
	void SetAnimationIndexBlend(int nIndex);

	// 애니메이션
	void AnimationConversion();

	void ReloadAction();
	void UpdateBulletText();
	void PlayerMotion();

	void BulletHit();
	OBB * GetOBB() { return m_pOBB; }
	void SetCurrHP(float hp) { m_fCurrHP = hp; }

public:
	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere_Item; }
	BulletManager* GetPBulletManager() { return m_pBM; }
};