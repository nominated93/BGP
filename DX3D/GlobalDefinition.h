#pragma once

#define CUBE_INDEX_SIZE 36
extern WORD g_aCubeIndex[];
#define CUBE_VERTEX_SIZE 8
extern D3DXVECTOR3 g_aCubeVertex[];


#define SINGLETON(class_name) private:\
	class_name();\
	~class_name();\
public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
		return &instance;\
	}

#define SAFE_WNDPROC(p) if(p) {(p)->WndProc(hWnd, message, wParam, lParam);}
#define SAFE_UPDATE(p) if(p) { (p)->Update();}
#define SAFE_RENDER(p) if(p) { (p)->Render();}
#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p) = NULL;}
#define SAFE_DELETE(p) if(p) { delete (p); (p) = NULL;}
#define SAFE_DELETE_ARRAY(p) { if(p) { delete [] p; p = NULL; } }

#define SYNTHESIZE(varType, varName, funName) \
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var) { varName = var; }

#define SYNTHESIZE_REF(varType, varName, funName) \
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var) { varName = var; }

#define SCREEN_POINT(lParam) LOWORD(lParam), HIWORD(lParam)

#define METHOD_WNDPROC(method) void method(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)

enum SCENE_INDEX {
	SCENE_OBJMAP
};

enum TAG_DISPLAYOBJECT {
	TAG_PLAYER
};

struct KEYBOARD_STATE
{
	D3DXVECTOR3 deltaPos;
	D3DXVECTOR3 deltaRot;
	bool bJump;
};

//	1. Position ������ ��ǥ x,y,z(float)				: D3DFVF_XYZ
// 	2. RHW (float)                                  : D3DFVF_XYZRHW (D3DFVF_XYZ �Ǵ� D3DFVF_NORMAL�� ���� ���Ұ�)
// 	3. Blending Weight Data ���� ����ġ (float)		: D3DFVF_XYZB1 ~ D3DFVF_XYZB5
// 	4. Vertex Normal ������ ���� ���� x,y,z(float)	: D3DFVF_NORMAL
// 	5. Vertex Point Size ������ �� ũ�� (float)		: D3DFVF_PSIZE
// 	6. Diffuse Color (DWORD)						: D3DFVF_DIFFUSE
// 	7. Specular Color (DWORD)						: D3DFVF_SPECULAR
// 	8. Texture Coordinate Set 1 (float)             : D3DFVF_TEX0 - D3DFVF_TEX8

struct VERTEX_PC
{
	D3DXVECTOR3 p;
	D3DCOLOR c;

	VERTEX_PC() {}
	VERTEX_PC(D3DXVECTOR3 _p, D3DCOLOR _c) :p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
};

struct VERTEX_PT
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;

	VERTEX_PT() {}
	VERTEX_PT(D3DXVECTOR3 _p, D3DXVECTOR2 _t) :p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1 };
};

struct VERTEX_PN
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;

	VERTEX_PN() {}
	VERTEX_PN(D3DXVECTOR3 _p, D3DXVECTOR3 _n) :p(_p), n(_n) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};

struct VERTEX_PNT
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;

	VERTEX_PNT() {}
	VERTEX_PNT(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t)
		:p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};

struct VERTEX_RHWC //w�� ����
{
	D3DXVECTOR4 p;
	D3DCOLOR	c;

	VERTEX_RHWC() {}
	VERTEX_RHWC(D3DXVECTOR4 _p, D3DCOLOR _c)
		:p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZRHW | D3DFVF_DIFFUSE };
};

struct MTLTEX : public BaseObject
{
	D3DMATERIAL9		material;
	LPDIRECT3DTEXTURE9	pTexture;
	int					id;

	MTLTEX() {
		ZeroMemory(&material, sizeof(D3DMATERIAL9));
		pTexture = NULL;
	}

	void SetMaterial(const D3DMATERIAL9 &_material)
	{
		material = _material;
	}
	D3DMATERIAL9 GetMaterial() { return material; }
	void SetTexture(LPDIRECT3DTEXTURE9 _pTexture)
	{
		pTexture = _pTexture;
	}
	LPDIRECT3DTEXTURE9 GetTexture() { return pTexture; }
};

struct ASE_POS_SAMPLE
{
	int			tick;
	D3DXVECTOR3 position;
};

struct ASE_ROT_SAMPLE
{
	int				tick;
	D3DXQUATERNION	quaternion;
};

struct ASE_SCENE
{
	int numFirstFrame;
	int numLastFrame;
	int frameSpeed;
	int ticksPerFrame;
};

struct BoundingSphere
{
	D3DXVECTOR3 center;
	float      radius;
	bool      isPicked;

	BoundingSphere() :isPicked(false) {}
	BoundingSphere(D3DXVECTOR3 _center, float _radius) :center(_center),
		radius(_radius), isPicked(false) {}
};

enum class ITEM_LIST
{
	AK47,
	ARMOR,
	END
};

enum class ITEM_INTO
{
	FIELD,
	INVEN,
	EQUIPMENT,
	END
};

//enum class ITEM_DRAGSTATE
//{
//	NORMAR,
//	DRAG,
//	DRAG_
//};

struct VERTEX_BLENDING
{
	D3DXVECTOR3 p;
	float   weight[3];
	DWORD   index;
	D3DXVECTOR2   t;

	VERTEX_BLENDING() {}
	VERTEX_BLENDING(D3DXVECTOR3 _p, float* _weight, DWORD _i, D3DXVECTOR2 _t)
		: p(_p), index(_i), t(_t)
	{
		weight[0] = _weight[0];
		weight[1] = _weight[1];
		weight[2] = _weight[2];
	}

	enum { FVF = D3DFVF_XYZB4 | D3DFVF_LASTBETA_UBYTE4 | D3DFVF_TEX1 };
};


extern DWORD FToDw(float f);

float GetRandomFloat(float lowBound, float highBound);