#pragma once
#include "IDisplayObject.h"

class Camera;

class Bullet : public IDisplayObject
{
private:
	LPD3DXMESH	m_pSphere;

private:
	bool		m_isFire;
	float		m_fSpeed;
	D3DXVECTOR3 m_vStartPos;


public:
	

public:
	Bullet();
	~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void Move();

	void Setup(D3DXVECTOR3* pos, D3DXVECTOR3* dir);

public:
	//D3DXVECTOR3 GetPosition() { return m_pos; }
	D3DXVECTOR3 GetStartPosition() { return m_vStartPos; }

	// Inherited via IUnitObject
};

