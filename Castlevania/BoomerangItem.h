#pragma once
#include "Item.h"

#define BOOMERANG_ITEM_GRAVITY			0.0005f
#define BOOMERANG_ITEM_BBOX_WIDTH		15
#define BOOMERANG_ITEM_BBOX_HEIGHT		15

class CBoomerangItem :
	public CItem
{
public:
	CBoomerangItem(D3DXVECTOR2 position);
	~CBoomerangItem();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
};

