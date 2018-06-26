#include "stdafx.h"
#include "GlobalDefinition.h"

WORD g_aCubeIndex[36] = {
	0, 1, 2, 0, 2, 3,	// ��
	7, 6, 5, 7, 5, 4,	// ��
	4, 5, 1, 4, 1, 0,	// ��
	3, 2, 6, 3, 6, 7,	// ��
	1, 5, 6, 1, 6, 2,	// ��
	4, 0, 3, 4, 3, 7	// ��
};

D3DXVECTOR3 g_aCubeVertex[8] = {
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f,  1.0f, -1.0f),
	D3DXVECTOR3(1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(-1.0f, -1.0f,  1.0f),
	D3DXVECTOR3(-1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f,  1.0f,  1.0f),
	D3DXVECTOR3(1.0f, -1.0f,  1.0f)
};

DWORD FToDw(float f)
{
	return *((DWORD *)&f);
}


float GetRandomFloat(float lowBound, float highBound)
{
	float f = (rand() % 10000) * 0.0001f;

	return f * (highBound - lowBound) + lowBound;
}