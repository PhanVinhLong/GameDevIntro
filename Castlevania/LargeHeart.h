#pragma once
#include "Item.h"

#define LARGE_HEART_GRAVITY			0.0005f
#define LARGE_HEART_BBOX_WIDTH		13
#define LARGE_HEART_BBOX_HEIGHT		10

class CLargeHeart :
	public CItem
{
public:
	CLargeHeart(D3DXVECTOR2 position);
	~CLargeHeart();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};
