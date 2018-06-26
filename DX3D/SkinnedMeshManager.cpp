#include "stdafx.h"
#include "SkinnedMeshManager.h"


SkinnedMeshManager::SkinnedMeshManager()
{
}


SkinnedMeshManager::~SkinnedMeshManager()
{
}

void SkinnedMeshManager::Setup(std::string  Name, IN char * szFolder, IN char * szFile)
{
	if (m_mapSkinnedMesh.find(Name) == m_mapSkinnedMesh.end())
	{
		m_mapSkinnedMesh[Name] = new SkinnedMesh();
		m_mapSkinnedMesh[Name]->Setup(szFolder, szFile);

	}
}

SkinnedMesh* SkinnedMeshManager::Find(std::string Name)
{
	if (m_mapSkinnedMesh.find(Name) != m_mapSkinnedMesh.end())
	{
		return m_mapSkinnedMesh[Name];
	}
	else
		return nullptr;
}

void SkinnedMeshManager::Destroy()
{
	for each(auto p in m_mapSkinnedMesh)
	{
		SAFE_DELETE(p.second);
	}
	m_mapSkinnedMesh.clear();
}
