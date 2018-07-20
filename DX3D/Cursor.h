#pragma once

#include "UIImage.h"

class Cursor :public IDisplayObject
{
private:
	UIImage *		m_pCursorImg;
	LPD3DXSPRITE	m_pSprite;

public:
	bool m_isClick;

public:
	Cursor();
	~Cursor();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

