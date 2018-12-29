#pragma once
#include "GameObject.h"
#include "GroundObject.h"

#define EASTER_EGG_BBOX_WIDTH	15
#define EASTER_EGG_BBOX_HEIGHT	5

class CEasterEgg :
	public CGameObject
{
	D3DXVECTOR2 destination;

	bool isTouched;
public:
	CEasterEgg(D3DXVECTOR2 position, D3DXVECTOR2 destination, int nextItemId);
	~CEasterEgg();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void BeTouched(vector<LPGAMEOBJECT>* objects);
};

