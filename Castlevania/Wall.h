#pragma once
#include "TransparentObject.h"
class CWall :
	public CTransparentObject
{
	int width;
	int height;
public:
	CWall();
	CWall(D3DXVECTOR2 position, int width, int height);
	~CWall();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
