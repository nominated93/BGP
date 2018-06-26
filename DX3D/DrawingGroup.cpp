#include "stdafx.h"
#include "DrawingGroup.h"


DrawingGroup::DrawingGroup()
{
	m_pVB = NULL;
	m_MtlTex = NULL;
}


DrawingGroup::~DrawingGroup()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_MtlTex);
}

void DrawingGroup::SetVertexBuffer(const vector<VERTEX_PNT>& vec)
{
	//������ ���� �������� �˾ƺ���!
	//D3DPOOL_SYSTEMMEM : �ý��� �⿡ ����
	//D3DPOOL_MANAGED : �ý��� ���̵� ���̵� �˾Ƽ� �͸�����ħ(���� �� �������, �׷��� ī�忡 �־�δ°� �����)
	//D3DPOOL_DEFAULT : �׷��� ī�忡 ����
	//���� �����ϱ�, �� �ڵ尡 �ǹ��ϴ� ���� �����ϱ�!?
	//����Ʈ�� �Ŵ����庸�� �ӵ��� �� ����
	//ù��° �ּ� �ǰ��߰�: �ý��� �޸� = RAM���� �����Ͻô°� �����ϴµ� ����ɰ� �����ϴ�
	g_pDevice->CreateVertexBuffer(vec.size() * sizeof(VERTEX_PNT), 0, VERTEX_PNT::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);
	
	m_numTri = vec.size() / 3;

	VERTEX_PNT * pVertices;
	m_pVB->Lock(0, 0, (LPVOID *)&pVertices, 0);
	memcpy(pVertices, &vec[0], vec.size() * sizeof(VERTEX_PNT));
	m_pVB->Unlock();
}

void DrawingGroup::Render()
{
	g_pDevice->SetTexture(0, m_MtlTex->pTexture);
	g_pDevice->SetMaterial(&m_MtlTex->material);
	g_pDevice->SetFVF(VERTEX_PNT::FVF);
	g_pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VERTEX_PNT));
	g_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_numTri);
}
