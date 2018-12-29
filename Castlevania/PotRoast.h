#pragma once
#include "Item.h"

#define POT_ROAST_ITEM_GRAVITY			0.0004f
#define POT_ROAST_ITEM_BBOX_WIDTH		20
#define POT_ROAST_ITEM_BBOX_HEIGHT		15

class CPotRoast :
	public CItem
{
public:
	CPotRoast(D3DXVECTOR2 position);
	~CPotRoast();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

