#pragma once
#include "Item.h"

#define HOLY_WATER_ITEM_GRAVITY				0.0005f
#define HOLY_WATER_ITEM_BBOX_WIDTH			15
#define HOLY_WATER_ITEM_BBOX_HEIGHT			15

class CHolyWaterPotion :
	public CItem
{
public:
	CHolyWaterPotion(D3DXVECTOR2 position);
	~CHolyWaterPotion();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

