#pragma once
#include "TransparentObject.h"

#define PORTAL_BBOX_WIDTH	12
#define PORTAL_BBOX_HEIGHT	10

class CPortal :
	public CTransparentObject
{
private:
	D3DXVECTOR2 destination;
public:
	CPortal(D3DXVECTOR2 position, D3DXVECTOR2 destination);
	~CPortal();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	D3DXVECTOR2 GetDestination();
};
