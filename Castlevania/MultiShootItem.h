#pragma once
#include "Item.h"

#define MULTI_SHOOT_ITEM_GRAVITY			0.0003f
#define MULTI_SHOOT_ITEM_BBOX_WIDTH			15
#define MULTI_SHOOT_ITEM_BBOX_HEIGHT		15

class CMultiShootItem :
	public CItem
{
public:
	CMultiShootItem(D3DXVECTOR2 position, int id = ID_DOUBLE_SHOOT);
	~CMultiShootItem();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

