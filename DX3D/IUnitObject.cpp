#include "stdafx.h"
#include "IUnitObject.h"
#include "AStar.h"
#include "AStarNode.h"


IUnitObject::IUnitObject()
{
	m_isMoving = false;
	m_moveSpeed = 0.2f;
	m_currMoveSpeedRate = 1.0f;
	m_rotationSpeed = 0.1f;

	m_isJumping = false;
	m_jumpPower = 1.0f;
	m_gravity = 0.05f;
	m_currGravity = 0.0f;

	m_maxStepHeight = 2.0f;
	speed = 0.0f;
	speed_max = 0.1f; 
	m_gSpeed = 0.000000000000f;
	Ani_Check = false;
	m_pos = D3DXVECTOR3(50, 1, 50);
	////m_destPos = D3DXVECTOR3(5,0,5);
}


IUnitObject::~IUnitObject()
{
}

void IUnitObject::SetDestination(const D3DXVECTOR3 & pos)
{
	//m_destPos = pos;

	m_vecAStarIndex.clear();
	m_destPos = m_pos;
	m_finalDestPos = pos;
	g_pCurrentMap->GetAStar()->FindPath(m_pos, pos, m_vecAStarIndex);
	g_pCurrentMap->GetAStar()->MakeDirectPath(m_pos, pos, m_vecAStarIndex);
}

void IUnitObject::UpdateKeyboardState()
{
	if (m_isJumping == false) m_isJumping = m_keyState.bJump;

	//m_deltaPos.z = m_keyState.deltaPos.z;
	m_deltaPos = m_keyState.deltaPos;
	//m_deltaPos.x = m_keyState.deltaPos.x;
	m_deltaRot.x = g_pCamera->m_rotX;
	m_deltaRot.y = g_pCamera->m_rotY;

	if (m_deltaPos.x == 0 && m_deltaPos.z == 0 && m_deltaRot.y == 0)
		return;

	D3DXMATRIXA16 matRX, matRY, matLeft, matRX2;
	//D3DXMatrixRotationX(&matRX, m_deltaRot.x * m_rotationSpeed);
	//D3DXMatrixRotationX(&matRX2, m_deltaRot.x * D3DX_PI / 2 * m_rotationSpeed);
	D3DXMatrixRotationY(&matRY, m_deltaRot.y * m_rotationSpeed);
	D3DXMatrixRotationY(&matLeft, m_deltaRot.y * D3DX_PI / 2 * m_rotationSpeed);
	D3DXVec3TransformNormal(&m_forward, &m_forward, &matRY);
	//D3DXVec3TransformNormal(&m_forward_test, &m_forward_test, &(matRY));
	D3DXVec3TransformNormal(&m_left, &m_left, &matLeft);

	//�̵� �ӵ� ���� ���
	m_destPos = D3DXVECTOR3(m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate);

	m_finalDestPos = m_destPos;
	m_vecAStarIndex.clear();
}

void IUnitObject::UpdatePositionToDestination()
{
	D3DXVECTOR3 targetPos = m_pos;
	UpdateTargetPosition(targetPos);
	ApplyTargetPosition(targetPos);

	D3DXMATRIXA16 m_matRotY;
	D3DXMatrixLookAtLH(&m_matRotY, &D3DXVECTOR3(0, 0, 0), &m_forward, &D3DXVECTOR3(0, 1, 0));
	D3DXMatrixTranspose(&m_matRotY, &m_matRotY);
	//ĳ���� ������ forward �������� ���ϰ� �ϴϱ�, baseRotation �߰��� ���� ������.
	D3DXMATRIXA16 matBaseR;
	D3DXMatrixRotationY(&matBaseR, m_baseRotY);

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	m_matWorld = m_matRotY * matBaseR * matT;

	if (D3DXVec3LengthSq(&m_deltaPos) > 0 || D3DXVec3LengthSq(&m_deltaRot) > 0)
		m_isMoving = true;
	else
		m_isMoving = false;
}

void IUnitObject::UpdateTargetPosition(OUT D3DXVECTOR3 & targetPos)
{
	//���� �̵��� ����
	D3DXVECTOR3 forward = D3DXVECTOR3(m_destPos.x - m_pos.x, 0, m_destPos.z - m_pos.z);
	D3DXVECTOR3 forwardNormalized = forward;

	//0���� ũ�� dest�� current�� �ٸ�����
	if (D3DXVec3LengthSq(&forward) > 0)
	{
		D3DXVec3Normalize(&forwardNormalized, &forwardNormalized);
		m_forward = forwardNormalized;
		//�����̵�
		if (m_deltaPos.z == 1)
		{
			//WŰ�� �̵��� ��
			m_currMoveSpeedRate = 1.0f;
		}
		//�ڷ� �̵�
		else if (m_deltaPos.z == -1)
		{
			//S Ű�� �̵��� ��
			m_currMoveSpeedRate = 0.5f;
			m_forward *= -1;
		}
		//���콺�� �Է½ÿ�
		else
		{
			m_currMoveSpeedRate = 1.0f;
			m_deltaPos.z = 1;

		}
		//�̵� �ӵ����� �Ÿ��� �� Ŭ �� 
		if (D3DXVec3Length(&forward) >= m_moveSpeed * m_currMoveSpeedRate)
		{
			targetPos = m_pos + forwardNormalized * m_moveSpeed * m_currMoveSpeedRate;
		}
		//�Ÿ��� �� �̵��ӵ����� ���� ��
		else
		{
			targetPos.x = m_destPos.x;
			targetPos.z = m_destPos.z;
		}
	}
	else if (m_vecAStarIndex.empty() == false)
	{
		//������ ���� �� AStar ��尡 �������� �� ������ �缳��
		m_destPos = g_pCurrentMap->GetAStar()->GetNodes()[m_vecAStarIndex.back()]->GetLocation();
		m_vecAStarIndex.pop_back();
	}
	else
	{
		m_destPos = m_finalDestPos;
	}
}

void IUnitObject::ApplyTargetPosition(D3DXVECTOR3 & targetPos)
{
	bool	isIntersected = true;
	float	height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;
		/*targetPos = m_pos + m_forward * m_deltapos.z
			* m_movespeed * m_currMoveSpeedRate;*/

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		/*targetPos = m_pos + m_forward * m_deltaPos.z
			* m_moveSpeed * m_currMoveSpeedRate;*/

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		//m_pos = targetPos;
	}
}

void IUnitObject::UpdatePosition()
{
	//m_rot += m_deltaRot;
	//m_rot.x = g_pCamera->m_rotX;
	//m_rot.y = g_pCamera->m_rotY;

	D3DXMATRIXA16 matRotY, matRotX, matRotTmp;
	D3DXVECTOR3 m_forward2;
	//D3DXMatrixRotationY(&matRotY, m_rot.y);
	//D3DXMatrixRotationX(&matRotX, g_pCamera->m_rotX);
	D3DXMatrixRotationY(&matRotY, g_pCamera->m_rotY);
	//D3DXMatrixRotationX(&matRotTmp, g_pCamera->m_rotX);
	D3DXVec3TransformNormal(&m_forward, &D3DXVECTOR3(0, 0, 1), &matRotY);
	//D3DXVec3TransformNormal(&m_forward2, &D3DXVECTOR3(1, 0, 0), &matRotX);
	//D3DXVec3TransformCoord(&m_forward_test, &(m_forward), &(-matRotX));
	//D3DXVec3TransformCoord(&m_forward_test, &D3DXVECTOR3(1, 0, 1), &(matRotX * matRotTmp));
	//D3DXVec3TransformCoord(&m_forward_test, &m_forward2, &(matRotY));
	//D3DXVec3TransformCoord(&m_forward_test, &D3DXVECTOR3(1, 0, 1), &(matRotX * matRotY));
	//D3DXVec3TransformCoord(&m_forward_test, &m_forward_test, &m_forward);
	//D3DXVec3TransformCoord(&m_forward_test, &matRotX, &(matRotY));
	D3DXVec3TransformNormal(&m_left, &D3DXVECTOR3(1, 0, 0), &matRotY);

	D3DXVECTOR3 targetPos;

	float	basePosY = 0;
	bool	isIntersected = true;
	float	height = 0;

	if (m_isJumping == true)
	{
		m_currMoveSpeedRate = 0.7f;

		//m_pos.x += m_deltaPos.x; //�߰�
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate
			+ m_left * m_deltaPos.x * m_moveSpeed * m_currMoveSpeedRate;

		//targetPos.x += m_deltaPos.x; //�߰�

		targetPos.y += m_jumpPower - m_currGravity;
		m_currGravity += m_gravity;

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
		}

		if (isIntersected == false)
		{
			if (g_pCurrentMap != NULL)
			{
				isIntersected = g_pCurrentMap->GetHeight(height, m_pos);
			}
			m_pos.y = targetPos.y;
		}
		else
		{
			m_pos = targetPos;
		}

		if (m_pos.y <= height && m_jumpPower < m_currGravity)
		{
			m_pos.y = height;
			m_isJumping = false;
			m_currGravity = 0;
			m_currMoveSpeedRate = 1.0f;
		}
		//m_pos = targetPos;
	}
	else //m_isJumping == false
	{
		//m_pos.x += m_deltaPos.x; //�߰�
		targetPos = m_pos + m_forward * m_deltaPos.z * m_moveSpeed * m_currMoveSpeedRate 
			+ m_left * m_deltaPos.x * m_moveSpeed * m_currMoveSpeedRate;
		//targetPos.x += m_deltaPos.x; //�߰�
		//targetPos += m_deltaPos; //�߰�

		if (g_pCurrentMap != NULL)
		{
			isIntersected = g_pCurrentMap->GetHeight(height, targetPos);
			int tmp = 0;
			if (isIntersected == false || fabs(height - m_pos.y) > m_maxStepHeight)
			{

			}
			else
			{
				targetPos.y = height;
				m_pos = targetPos;
			}
		}
		else
		{
			m_pos = targetPos;
		}

		m_pos = targetPos;
	}
	
	//m_pos = targetPos;
	//m_pos.x = targetPos.x;

	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&matT, m_pos.x, m_pos.y, m_pos.z);
	////D3DXMatrixRotationY(&matRotY, m_rot.y + m_baseRotY);
	//D3DXMatrixRotationY(&matRotY, m_rot.y);
	//m_matWorld = matRotY * matT;

	//if (D3DXVec3LengthSq(&m_deltaRot) > D3DX_16F_EPSILON || D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
	if (D3DXVec3LengthSq(&m_deltaPos) > D3DX_16F_EPSILON)
		m_isMoving = true;
	else

		m_isMoving = false;
}
