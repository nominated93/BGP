#pragma once
#include "IUIObject.h"
class UIImage :
	public IUIObject
{
public:
	LPDIRECT3DTEXTURE9	m_pTex;
	D3DXIMAGE_INFO		m_info;

	UIImage(LPD3DXSPRITE pSprite, int uiTag = -1);
	virtual ~UIImage();

	virtual void Update() override;
	virtual void Render() override;
	void SetTexture(string fullPath);
};

