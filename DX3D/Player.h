#pragma once
#include "IUnitObject.h"
#include "ProgressBarManager.h"

class SkinnedMesh;
class UIImage;
class UIText;
class BulletManager;
class OBB;
class Inventory;

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
	LPD3DXSPRITE			m_pSprite;
	LPD3DXMESH				m_pMesh;
	BulletManager*			m_pBM;
	ProgressBarManager*		m_pPB;
	OBB*					m_pOBB;		
	Inventory*				m_pInven;
	D3DXMATRIXA16			matWorld;
	Mesh*					m_pGun;
	SYNTHESIZE(bool, m_isAlive, IsAlive);

private:
	int						m_eState;
	ePlayerState			m_ePlayerState;


private:
	char					m_bulletCntStr[1024];
	char					m_bulletTotalStr[1024];
	string					m_szCurrentFile;

private:
	int						m_bulletCurrCnt;
	int						m_bulletTotalCnt;

private:
	float					 m_fCurrHP;
	float					 m_fMaxHP;

private:
	BoundingSphere			m_tCollisionSphere_Item;

	//D3DXMATRIXA16 matS, matRX, matRY, matT, matWorld, matBone;
private:

	bool						m_isZoom;
	bool						m_isReload;
	bool						m_isInven;

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

	void SetCurrHP(float hp) { m_fCurrHP = hp; }

public:
	BoundingSphere GetCollisionSphere() { return m_tCollisionSphere_Item; }
	BulletManager* GetPBulletManager() { return m_pBM; }
	Inventory* GetPInven() { return m_pInven; }
	OBB * GetOBB() { return m_pOBB; }
};