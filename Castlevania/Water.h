#pragma once
#include "TransparentObject.h"
class CWater :
	public CTransparentObject
{
	int width;
	int height;
public:
	CWater();
	CWater(D3DXVECTOR2 position, int width, int height);
	~CWater();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

