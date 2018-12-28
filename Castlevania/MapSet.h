#pragma once
#include "GameObject.h"

#define MAPSET_BBOX_WIDTH	30
#define MAPSET_BBOX_HEIGHT	18

class CMapSet :
	public CGameObject
{
	int wBegin;
	int wEnd;
public:
	CMapSet(D3DXVECTOR2 position, int wBegin, int wEnd);
	~CMapSet();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();

	int GetWidthBegin() { return wBegin; }
	int GetWidthEnd() { return wEnd; }
};

