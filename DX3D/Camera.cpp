#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	m_distance = 10.0f;
	m_basePosY = 5.0f;
	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);
	m_lookAt = D3DXVECTOR3(0, 0, 0);
	m_up = D3DXVECTOR3(0, 1, 0);
	m_rotX = 0.0f;
	m_rotY = 0.0f;
	m_isLbuttonDown = false;
	m_pTarget = NULL;
}


Camera::~Camera()
{
}

void Camera::Init()
{
	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);


	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1, 1000);
	g_pDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void Camera::Update()
{
	m_eye = D3DXVECTOR3(0, m_basePosY, -m_distance);

	D3DXMATRIXA16 matRotX, matRotY, matRot;
	D3DXMatrixRotationX(&matRotX, m_rotX);
	D3DXMatrixRotationY(&matRotY, m_rotY);
	
	matRot = matRotX * matRotY;

	D3DXVec3TransformCoord(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRot);
	//D3DXVec3TransformCoord(&m_forward, &D3DXVECTOR3(0,0,1), &matRot);


	D3DXVec3TransformCoord(&m_eye, &m_eye, &matRot);

	if (m_pTarget)
	{
		m_lookAt = *m_pTarget;
		m_eye = m_eye + *m_pTarget;
		
		m_lookAt.y += 10.0f;
		m_eye.y += 10.0f;
		//m_up.y -= 15;

		//D3DXVECTOR3 temp;
		//float distance = 10.0f;
		//temp = (static_cast <IUnitObject *> (g_pObjMgr->FindObjectByTag(TAG_PLAYER))->GetForward()) + (*m_pTarget);

		//m_lookAt = D3DXVECTOR3(temp.x, temp.y + 10, temp.z);
		//m_eye = *m_pTarget + m_eye;
	}

	D3DXMatrixLookAtLH(&m_matView, &m_eye, &m_lookAt, &m_up);
	g_pDevice->SetTransform(D3DTS_VIEW, &m_matView);

}

void Camera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_isLbuttonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isLbuttonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		/*if (m_isLbuttonDown == true)
		{*/
			POINT currPoint;
			currPoint.x = LOWORD(lParam);
			currPoint.y = HIWORD(lParam);

			m_rotY += (currPoint.x - m_ptPrevMouse.x) / 100.0f;
			m_rotX += (currPoint.y - m_ptPrevMouse.y) / 100.0f;

			if (m_rotX <= -D3DX_PI * 0.5f + D3DX_16F_EPSILON)
			{
				m_rotX = -D3DX_PI * 0.5f + D3DX_16F_EPSILON;
			}
			if (m_rotX >= D3DX_PI * 0.3f - D3DX_16F_EPSILON)
			{
				m_rotX = D3DX_PI * 0.3f - D3DX_16F_EPSILON;
			}

			m_ptPrevMouse = currPoint;

/*
			RECT rc2;
			GetClientRect(g_hWnd, &rc2);

			POINT it, rb;
			it.x = rc2.left; it.y = rc2.right; rb.x = rc2.top; rb.y = rc2.bottom;

			ClientToScreen(g_hWnd, &it); ClientToScreen(g_hWnd, &rb);
			rc2.left = it.x; rc2.top = it.y; rc2.right = rb.x; rc2.bottom = rb.y;

			ClipCursor(&rc2);*/
		/*}*/
	}
	break;
	/*
	case WM_MOUSEWHEEL:
		m_distance -= GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
		if (m_distance <= 10) m_distance = 10;
		if (m_distance >= 30) m_distance = 30;
		break;
	*/
	}

}
