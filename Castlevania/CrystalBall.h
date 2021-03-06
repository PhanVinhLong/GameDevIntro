#pragma once
#include "Item.h"

#define CRYSTAL_BALL_GRAVITY			0.0002f
#define CRYSTAL_BALL_BBOX_WIDTH			15
#define CRYSTAL_BALL_BBOX_HEIGHT		15

class CCrystalBall :
	public CItem
{
public:
	CCrystalBall(D3DXVECTOR2 position);
	~CCrystalBall();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

