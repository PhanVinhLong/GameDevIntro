#pragma once
#include "GroundObject.h"

#define CANDLE_BBOX_WIDTH	8
#define CANDLE_BBOX_HEIGHT	15

class CCandle :
	public CGroundObject
{
public:
	CCandle(D3DXVECTOR2 position, int nextItemTypeID);
	~CCandle();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
