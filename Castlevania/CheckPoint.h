#pragma once
#include "GroundObject.h"

#define CHECKPOINT_BBOX_WIDTH	20
#define CHECKPOINT_BBOX_HEIGHT	30

class CCheckPoint :
	public CGroundObject
{
public:
	CCheckPoint(D3DXVECTOR2 position);
	~CCheckPoint();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};

