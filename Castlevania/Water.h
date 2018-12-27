#pragma once
#include "GroundObject.h"
class CWater :
	public CGroundObject
{
	int width;
	int height;
public:
	CWater();
	CWater(D3DXVECTOR2 position, int width, int height);
	~CWater();

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

