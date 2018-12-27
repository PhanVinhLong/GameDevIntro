#include "Item.h"

#define CROSS_ITEM_GRAVITY			0.0005f
#define CROSS_ITEM_BBOX_WIDTH		15
#define CROSS_ITEM_BBOX_HEIGHT		15

#pragma once
class CCrossItem :
	public CItem
{
public:
	CCrossItem(D3DXVECTOR2 position);
	~CCrossItem();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

