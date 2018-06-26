#pragma once
#include "IDisplayObject.h"
//�����ٰ� �׳� �ϸ� �������� ���ϱ�, 3������ �׸��� �뵵�� Ŭ������ ���θ���.
class Picking :
	public IDisplayObject
{
private:
	RECT rc;
	LPD3DXMESH m_pSphere;
	vector<BoundingSphere*> m_vecBoundary;

public:
	Picking();
	~Picking();

	// IDisplayObject��(��) ���� ��ӵ�
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

