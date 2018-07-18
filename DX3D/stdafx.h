// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#include <assert.h>//���μ��� ų ������ ���� ���
#include <vector>
#include <map>
#include <set>
#include <list>
#include <fstream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "fmod_vc")

#include <string>
#include <atlstr.h>

using namespace std;
using std::to_string;

extern HWND g_hWnd;

#include "BaseObject.h"

#include "Application.h"
#include "GlobalDefinition.h"

#include <bitset>
#include "DX.h"

#include "DeviceManager.h"

#include "Camera.h"

#include "AllocateHierarchy.h"
#include "SkinnedMesh.h"

#include "KeyboardManager.h"

#include "IMap.h"
#include "IUnitObject.h"

#include "Debug.h"

#include "BulletManager.h"

#include "MapManager.h"
#include "Mesh.h"
#include "MeshManager.h"
#include "SkinnedMeshManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "ObjManager.h"
#include "CSoundManager.h"
