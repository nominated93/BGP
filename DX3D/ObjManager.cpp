#include "stdafx.h"
#include "ObjManager.h"


ObjManager::ObjManager()
{
}


ObjManager::~ObjManager()
{
}

void ObjManager::AddObject(BaseObject * pObj)
{
	m_setObject.insert(pObj);
}

void ObjManager::RemoveObject(BaseObject * pObj)
{
	m_setObject.erase(pObj);
}

void ObjManager::Destroy()
{
	assert(m_setObject.empty() && "������ ��ü �� �������� ���� ��ü�� �ֽ��ϴ�.");
}

void ObjManager::AddToTagList(WORD _tag, IDisplayObject * _pObj)
{
	m_tagList[_tag].push_back(_pObj);
}

void ObjManager::RemoveFromTagList(WORD _tag, IDisplayObject * _pObj)
{
	m_tagList[_tag].remove(_pObj);
}

IDisplayObject * ObjManager::FindObjectByTag(WORD _tag)
{
	if (m_tagList[_tag].empty() == true)
		return NULL;

	return m_tagList[_tag].front();
}

list<IDisplayObject*> ObjManager::FindObjectsByTag(WORD _tag)
{
	return m_tagList[_tag];
}
