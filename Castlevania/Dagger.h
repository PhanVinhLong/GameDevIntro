#pragma once
#include "Weapon.h"

#define DAGGER_BBOX_WIDTH	20
#define DAGGER_BBOX_HEIGHT	8

#define DAGGER_SPEED		0.2f

class CDagger :
	public CWeapon
{
public:
	CDagger(D3DXVECTOR2 position, int nx);
	~CDagger();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

