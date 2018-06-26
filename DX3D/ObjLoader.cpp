#include "stdafx.h"
#include "ObjLoader.h"
#include "DrawingGroup.h"

ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}

void ObjLoader::Load(const char * filePath, const char * fileName, D3DXMATRIXA16 * pMat, OUT vector<DrawingGroup*>& vecGroup)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<VERTEX_PNT> vecPNT;
	string mtlName;

	char szToken[128];
	std::ifstream fin;

	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;

	fin.open(fullPath);

	if (fin.is_open() == false)
		return;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "mtllib"))
		{
			string fileName;
			fin >> fileName;
			fileName = m_filePath + "/" + fileName;

			LoadMtlLib(fileName.c_str());
		}
		else if (CompareStr(szToken, "g"))
		{
			if (vecPNT.empty()) continue;

			DrawingGroup* pGroup = new DrawingGroup;

			pGroup->SetVertexBuffer(vecPNT);
			pGroup->SetMtlTex(m_mapMtlTex[mtlName]);
			m_mapMtlTex[mtlName]->AddRef();

			vecGroup.push_back(pGroup);
			vecPNT.clear();
		}
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f *%f", &x, &y);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3][3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%d/%d %d/%d/%d %d/%d/%d",
				&aIndex[0][0], &aIndex[0][1], &aIndex[0][2],
				&aIndex[1][0], &aIndex[1][1], &aIndex[1][2],
				&aIndex[2][0], &aIndex[2][1], &aIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				VERTEX_PNT pnt;
				pnt.p = vecP[aIndex[i][0] - 1];
				pnt.t = vecT[aIndex[i][1] - 1];
				pnt.n = vecN[aIndex[i][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
					D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
				}
				vecPNT.push_back(pnt);
			}
		}
	}

	for (auto p : m_mapMtlTex)
		SAFE_RELEASE(p.second);

	m_mapMtlTex.clear();
	fin.close();
}

void ObjLoader::LoadSurface(const char * fullpath, D3DXMATRIXA16 * pMat, OUT vector<D3DXVECTOR3>& vecVertex)
{
	vector<D3DXVECTOR3> vecP;

	char szToken[128];
	std::ifstream fin;

	fin.open(fullpath);

	if (fin.is_open() == false)
		return;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}

		else if (CompareStr(szToken, "f"))
		{
			int aIndex[3];
			fin.getline(szToken, 128);

			sscanf_s(szToken, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);

			for (int i = 0; i < 3; i++)
			{

				D3DXVECTOR3 v = vecP[aIndex[i] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&v, &v, pMat);
				}
				vecVertex.push_back(v);
			}
		}
	}

	fin.close();
}

//loader.LoadMesh("resources/obj", "Map.obj", &matWorld, m_vecMtlTex);	// �޽� �ε�
LPD3DXMESH ObjLoader::LoadMesh(const char* filePath, const char* fileName, D3DXMATRIXA16* pMat, OUT vector<MTLTEX*>& vecMtlTex)
{
	vector<D3DXVECTOR3> vecP;
	vector<D3DXVECTOR2> vecT;
	vector<D3DXVECTOR3> vecN;
	vector<VERTEX_PNT> vecPNT;
	vector<DWORD> vecAttBuf; //�Ӽ�����
	string mtlName;

	char szToken[128];
	std::ifstream fin;

	m_filePath = filePath;
	string fullPath = m_filePath + "/" + fileName;

	fin.open(fullPath);

	if (fin.is_open() == false)
		return NULL;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "mtllib"))
		{
			string fileName;
			fin >> fileName;

			if (!m_filePath.empty())
				fileName = m_filePath + "/" + fileName;

			LoadMtlLib(fileName.c_str());

			// �ε� �� MtlTex�� ID�� SubSet�� ID�� ������
			vecMtlTex.resize(m_mapMtlTex.size());
			for (auto p : m_mapMtlTex)
				vecMtlTex[p.second->id] = p.second; //MtlTex id�� �ε����� �°� �־��ش� 0�� ������� ����Ҷ� 0�� mtltex�� ����Ѵ�

		}
		else if (CompareStr(szToken, "v"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecP.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "vt"))
		{
			float x, y;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f *%f", &x, &y);
			vecT.push_back(D3DXVECTOR2(x, y));
		}
		else if (CompareStr(szToken, "vn"))
		{
			float x, y, z;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &x, &y, &z);
			vecN.push_back(D3DXVECTOR3(x, y, z));
		}
		else if (CompareStr(szToken, "usemtl"))
		{
			fin >> szToken;
			mtlName = szToken;
		}
		else if (CompareStr(szToken, "f"))
		{
			// 3�� �Ǵ� 4���� ������ �޴� �ε���
			int aIndex[4][3];
			fin.getline(szToken, 128);

			char* context = NULL;
			char* ptr = strtok_s(szToken, " ", &context);
			int idxNum = 0;

			while (ptr)
			{
				sscanf_s(ptr, "%d/%d/%d",
					&aIndex[idxNum][0], &aIndex[idxNum][1], &aIndex[idxNum][2]);

				idxNum++;
				ptr = strtok_s(NULL, " ", &context);
			}

			// ���� 3���� ����
			if (idxNum == 3)
			{
				for (int i = 0; i < 3; i++)
				{
					VERTEX_PNT pnt;
					pnt.p = vecP[aIndex[i][0] - 1];
					pnt.t = vecT[aIndex[i][1] - 1];
					pnt.n = vecN[aIndex[i][2] - 1];

					if (pMat)
					{
						D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
						D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
					}
					vecPNT.push_back(pnt);
				}

				vecAttBuf.push_back(m_mapMtlTex[mtlName]->id); //���ϳ��� �Ӽ� id �ϳ�
			}
			// ���� 4���� ����
			else if (idxNum == 4)
			{
				// 0 1 2
				for (int i = 0; i < 3; i++)
				{
					VERTEX_PNT pnt;
					pnt.p = vecP[aIndex[i][0] - 1];
					pnt.t = vecT[aIndex[i][1] - 1];
					pnt.n = vecN[aIndex[i][2] - 1];

					if (pMat)
					{
						D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
						D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
					}
					vecPNT.push_back(pnt);
				}

				vecAttBuf.push_back(m_mapMtlTex[mtlName]->id); //���ϳ��� �Ӽ� id �ϳ�


															   // 0 2 3
				VERTEX_PNT pnt0;
				pnt0.p = vecP[aIndex[0][0] - 1];
				pnt0.t = vecT[aIndex[0][1] - 1];
				pnt0.n = vecN[aIndex[0][2] - 1];

				if (pMat)
				{
					D3DXVec3TransformCoord(&pnt0.p, &pnt0.p, pMat);
					D3DXVec3TransformNormal(&pnt0.n, &pnt0.n, pMat);
				}
				vecPNT.push_back(pnt0);

				for (int i = 2; i <= 3; i++)
				{
					VERTEX_PNT pnt;
					pnt.p = vecP[aIndex[i][0] - 1];
					pnt.t = vecT[aIndex[i][1] - 1];
					pnt.n = vecN[aIndex[i][2] - 1];

					if (pMat)
					{
						D3DXVec3TransformCoord(&pnt.p, &pnt.p, pMat);
						D3DXVec3TransformNormal(&pnt.n, &pnt.n, pMat);
					}
					vecPNT.push_back(pnt);
				}

				vecAttBuf.push_back(m_mapMtlTex[mtlName]->id); //���ϳ��� �Ӽ� id �ϳ�
			}


		}
	}

	m_mapMtlTex.clear();
	fin.close();

	/* �Ž����� �� ���� ä���, ����ȭ */
	LPD3DXMESH pMesh = NULL;

	// ���, ���ý� ��, �������� �ٸ��͵�� ����!
	// WORD�� �ִ� ũ�Ⱑ 65536(16��Ʈ)�̹Ƿ� �Ѿ�� 32��Ʈ�� ��ȯ����
	//if(vecPNT.size() >= 65536)
	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_PNT::FVF, g_pDevice, &pMesh);
	//else
	//	D3DXCreateMeshFVF(vecPNT.size() / 3, vecPNT.size(), D3DXMESH_MANAGED, VERTEX_PNT::FVF, g_Device, &pMesh);

	//1. ���� 3�� ������!!!
	// ���ؽ� ����
	VERTEX_PNT* pV = NULL;
	DWORD flags = 0;
	pMesh->LockVertexBuffer(flags, (LPVOID*)&pV);
	memcpy(pV, &vecPNT[0], vecPNT.size() * sizeof(VERTEX_PNT));
	pMesh->UnlockVertexBuffer();

	// �ε��� ����
	DWORD* pI = NULL;
	pMesh->LockIndexBuffer(flags, (LPVOID*)&pI);
	for (size_t i = 0; i < vecPNT.size(); ++i)
		pI[i] = static_cast<DWORD>(i);
	pMesh->UnlockIndexBuffer();

	// ��Ʈ����Ʈ ����
	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(flags, &pA);
	memcpy(pA, &vecAttBuf[0], vecAttBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	// 2. �������� ����
	vector<DWORD> vecAdjacency(pMesh->GetNumFaces() * 3);
	pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjacency[0]);

	//DWORD* aAdjacency = new DWORD[pMesh->GetNumFaces() * 3];
	//pMesh->GenerateAdjacency(1e-6f, aAdjacency);
	//pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, aAdjacency, NULL, NULL, NULL);

	// 3. ����ȭ
	// �޽��� �� �� ������ ���� ������ ������, �����ս��� ����ȭ�Ѵ�.
	pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, &vecAdjacency[0], 0, 0, 0);
	//SAFE_DELETE_ARRAY(aAdjacency);

	return pMesh;
}

void ObjLoader::LoadMtlLib(string fullPath)
{
	string mtlName;
	DWORD mtltexID = 0;		// ID ����

	char szToken[128];
	std::ifstream fin;

	fin.open(fullPath);

	if (fin.is_open() == false)
		return;

	while (fin.eof() == false)
	{
		fin >> szToken;

		if (CompareStr(szToken, "newmtl"))
		{
			fin >> mtlName;

			SAFE_RELEASE(m_mapMtlTex[mtlName]);
			m_mapMtlTex[mtlName] = new MTLTEX;
			m_mapMtlTex[mtlName]->id = mtltexID++;	// MTLTEX �����ø��� �ٸ� ���̵� �������� ++�� ������
		}
		else if (CompareStr(szToken, "Ka"))
		{
			D3DCOLORVALUE c;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Ambient = c;
		}
		else if (CompareStr(szToken, "Kd"))
		{
			D3DCOLORVALUE c;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Diffuse = c;
		}
		else if (CompareStr(szToken, "Ks"))
		{
			D3DCOLORVALUE c;
			fin.getline(szToken, 128);
			sscanf_s(szToken, "%f %f %f", &c.r, &c.g, &c.b);
			c.a = 1.0f;
			m_mapMtlTex[mtlName]->material.Specular = c;
		}
		else if (CompareStr(szToken, "map_Kd"))
		{
			string filename;
			fin >> filename;
			filename = m_filePath + "/" + filename;

			m_mapMtlTex[mtlName]->SetTexture(
				g_pTextureManager->GetTexture(filename));
		}
	}

	fin.close();
}

bool ObjLoader::CompareStr(char * str1, const char * str2)
{
	return strcmp(str1, str2) == 0;
}

void ObjLoader::CreateSurface(OUT vector<D3DXVECTOR3>& vecVertex)
{
	vecVertex.reserve(vecPNT.size() / 3);
	for (size_t i = 0; i < vecPNT.size(); i += 3)
	{
		D3DXVECTOR3 normal;
		DXUtil::ComputeNormal(&normal, &vecPNT[i].p, &vecPNT[i + 1].p, &vecPNT[i + 2].p);
		if (D3DXVec3Dot(&normal, &D3DXVECTOR3(0, 1, 0)) > 0.4f)
		{
			vecVertex.push_back(vecPNT[i].p);
			vecVertex.push_back(vecPNT[i + 1].p);
			vecVertex.push_back(vecPNT[i + 2].p);
		}
	}
}
