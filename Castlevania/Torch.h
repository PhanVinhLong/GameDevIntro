#pragma once
#include "GroundObject.h"

#define TORCH_BBOX_WIDTH		18
#define TORCH_BBOX_HEIGHT		30

class CTorch :
	public CGroundObject
{
public:
	CTorch(D3DXVECTOR2 position, int nextItemTypeId);
	~CTorch();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
