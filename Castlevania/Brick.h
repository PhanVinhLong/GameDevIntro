#pragma once
#include "GroundObject.h"
#include "BrickEffect.h"

#define BRICK_BBOX_WIDTH	16
#define BRICK_BBOX_HEIGHT	13

class CBrick :
	public CGroundObject
{
	bool isBroken;
public:
	CBrick(D3DXVECTOR2 position, int nextItemTypeID);
	~CBrick();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void BeDamaged();
};

