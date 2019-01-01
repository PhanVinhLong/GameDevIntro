#pragma once
#include "Item.h"

#define SMALL_HEART_GRAVITY			0.0003f
#define SMALL_HEART_BBOX_WIDTH		8
#define SMALL_HEART_BBOX_HEIGHT		8

#define SMALL_HEART_DELTA_X			0.0436f
#define SMALL_HEART_AMPLITUDE_X		15

class CSmallHeart :
	public CItem
{
	float originX;
	float delta;
public:
	CSmallHeart(D3DXVECTOR2 position);
	~CSmallHeart();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

