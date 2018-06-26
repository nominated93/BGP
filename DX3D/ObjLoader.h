#pragma once

class DrawingGroup;

class ObjLoader
{
public:
	vector<VERTEX_PNT>		vecPNT;

	string					m_filePath;
	map<string, MTLTEX*>	m_mapMtlTex;

	ObjLoader();
	~ObjLoader();

	// OUT -> Load�� ���� �ű⿡ �־��ְڴ�
	// �̰� �Ⱦ�
	void Load(const char* filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<DrawingGroup*> &vecGroup);
	void LoadSurface(const char* fullpath, D3DXMATRIXA16* pMat, OUT vector<D3DXVECTOR3> &vecVertex);

	// .Obj ������ �ε��ϴ� �޼���
	// filePath = ���, fileName = �����̸�, pMat = �����Ʈ����, vecGroup = ������ OUT�� ���ؽ� ����
	LPD3DXMESH LoadMesh(const char* filePath, const char* fileName, D3DXMATRIXA16 *pMat, OUT vector<MTLTEX*> &vecMtlTex);

	// mtl���̺귯�� ȣ��
	void LoadMtlLib(string fullpath);
	bool CompareStr(char* str1, const char* str2);

	void CreateSurface(OUT vector<D3DXVECTOR3> &vecVertex);
};

