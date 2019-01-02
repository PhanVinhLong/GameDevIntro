#pragma once
#include "TransparentObject.h"

#define CHECKPOINT_BBOX_WIDTH	20
#define CHECKPOINT_BBOX_HEIGHT	30

class CCheckPoint :
	public CTransparentObject
{
public:
	CCheckPoint(D3DXVECTOR2 position);
	~CCheckPoint();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};

