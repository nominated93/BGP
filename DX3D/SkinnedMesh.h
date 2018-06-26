#pragma once
#include  "IUnitObject.h"

class SkinnedMesh : public IUnitObject
{
protected:
	//LPD3DXFRAME		m_pRoot;
	//LPD3DXANIMATIONCONTROLLER	m_pAnimationController;

	SYNTHESIZE(LPD3DXFRAME, m_pRoot, Root);
	SYNTHESIZE(LPD3DXANIMATIONCONTROLLER, m_pAnimationController, AnimationController);


	float		m_fPassedBlendTime;
	float		m_fBlendTime;
	bool		m_isBlend;

	/* 추가 */
	UINT							m_AnimNum;
	typedef std::map< std::string, LPD3DXANIMATIONSET >			MAP_ANIMSET;
	typedef std::vector< LPD3DXANIMATIONSET >					VEC_ANIMSET;
	SYNTHESIZE(MAP_ANIMSET, m_mapAnimSet, mapAnimSet);
	VEC_ANIMSET						m_vecAnimSet;

	SYNTHESIZE(D3DXVECTOR3, m_vMin, Min); 
	SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);

	D3DXTRACK_DESC					m_TrackDesc;
	LPD3DXANIMATIONSET				m_pAniSet;

	SYNTHESIZE(bool, m_bPlay, Play);
	SYNTHESIZE(bool, m_bLoop, Loop);
	SYNTHESIZE(bool, m_bCheck, Check);
	SYNTHESIZE(LPD3DXANIMATIONSET, m_pPrevPlayAnimationSet, PrevPlayAnimationSet);	// Standard Animation set or Prev Animation set

	float							m_fCrossFadeTime;
	float							m_fLeftCrossFadeTime;
	float							m_fOutCrossFadeTime;
	double							m_AnimationPlayFactor;		// Current Animation Frame Time
	float							m_fAnimDelta;				// Ellapsed Time

private:
	SYNTHESIZE(float, m_fRotY, fRotY); 
	SYNTHESIZE(D3DXVECTOR3, m_vPos, Position); 
	SYNTHESIZE(D3DXVECTOR3, m_vDir, Direction); 
	SYNTHESIZE(D3DXVECTOR3, m_vPlayerPos, PlayerPos); 
	/* 추가 끝 */

public:
	SkinnedMesh();
	~SkinnedMesh();

	void Setup(IN char* szFolder, IN char* szFile);
	//void Update(float timeDelta);
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame, D3DXMATRIXA16* m_World);

	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	// animation
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);

	// Inherited via IUnitObject
	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
	 
};