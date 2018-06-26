#include "stdafx.h"
#include "KeyboardManager.h"


KeyboardManager::KeyboardManager()
{
}


KeyboardManager::~KeyboardManager()
{
}

void KeyboardManager::Update()
{
	UpdateMoving();
}
/*
�ڽ��� ���� pos rot ������ �ƴ� deltaPos deltaRot ���� �߰� �Ŀ� �� ������ keyboardManager->setTarget �� �����ϱ�
delta ���� 0 �� �ƴϸ� �̵� �� ȸ�� �����ϱ�

Ű�Ŵ��� ���� �� ���� ����
���ø����̼� ���� �κп��� ���Ŵ��� ȣ��
���ø����̼� ���� �κп��� Ű���� �Ŵ��� ������Ʈ
������ ������Ʈ �ϸ�
ť��ǿ��� ������Ʈ ����
ť��� ������Ʈ �����ǿ���
Ű�Ŵ��� �޾ƿ�(��Ÿ ��)��������
ť��� ������Ʈ ������ �Լ� ������ ����
*/
void KeyboardManager::UpdateMoving()
{
	if (m_pKeyState == NULL)
		return;

	//���ȳ� �� ���ȳĸ� üũ���ִ� ����� ������.
	if (GetKeyState('A') & 0x08000)
	{
		//m_pTargetRot->y = -1;
		m_pKeyState->deltaPos.x = -1;
		
		//m_pTargetPos->x = -1;
	}
	else if (GetKeyState('D') & 0x08000)
	{
		//m_pTargetRot->y = 1;
		m_pKeyState->deltaPos.x = 1;
		//m_pTargetPos->x = 1;
	}
	else
	{
		m_pKeyState->deltaPos.x = 0;
	}

	if (GetKeyState('W') & 0x8000)
	{
		m_pKeyState->deltaPos.z = 1;
	}
	else if (GetKeyState('S') & 0x8000)
	{
		m_pKeyState->deltaPos.z = -1;
	}
	else
	{
		m_pKeyState->deltaPos.z = 0;
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
		m_pKeyState->bJump = true;
	else
		m_pKeyState->bJump = false;


	if (GetAsyncKeyState(VK_LEFT) & 0x0001)
	{
		m_pTargetRot->y = (D3DX_PI/2) * 10;
	}
	else if (GetAsyncKeyState(VK_RIGHT) & 0x0001)
	{
		m_pTargetRot->y = -(D3DX_PI / 2) * 10;
	}

}
//Ű���� ���� ��Ű�� ���� ��ü�� �̵��� ȸ���� ���� ���� �״ϱ� �� ��ü���� Ű���� ���� �ֱ� ���� �Ѱ�����.
void KeyboardManager::SetMovingTarget(D3DXVECTOR3 * pPos, D3DXVECTOR3 * pRot, bool * pIsJumping)
{
	m_pTargetPos = pPos;
	m_pTargetRot = pRot;
	m_pTargetIsJumping = pIsJumping;
}

bool KeyboardManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	return false;
}

bool KeyboardManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;

}