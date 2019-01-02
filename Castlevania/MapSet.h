#pragma once
#include "TransparentObject.h"

#define MAPSET_BBOX_WIDTH	30
#define MAPSET_BBOX_HEIGHT	18

class CMapSet :
	public CTransparentObject
{
	int wBegin;
	int wEnd;
public:
	CMapSet(D3DXVECTOR2 position, int wBegin, int wEnd);
	~CMapSet();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	int GetWidthBegin() { return wBegin; }
	int GetWidthEnd() { return wEnd; }
};

