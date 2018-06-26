#pragma once

#define g_pSkinnedMeshManager SkinnedMeshManager::GetInstance()

#include "SkinnedMesh.h"
class SkinnedMeshManager
{
private:
	SINGLETON(SkinnedMeshManager);
private:
	std::map<std::string, SkinnedMesh*> m_mapSkinnedMesh;
public:

	void Setup(std::string  Name, IN char* szFolder, IN char* szFile);
	SkinnedMesh* Find(std::string Name);

	void Destroy();
};