#pragma once
#include "Item.h"

#define AXE_ITEM_GRAVITY			0.0005f
#define AXE_ITEM_BBOX_WIDTH			15
#define AXE_ITEM_BBOX_HEIGHT		15

class CAxeItem :
	public CItem
{
public:
	CAxeItem(D3DXVECTOR2 position);
	~CAxeItem();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

