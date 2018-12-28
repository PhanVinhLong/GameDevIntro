#pragma once
#include "Weapon.h"
#include "Simon.h"

#define BOOMERANG_BBOX_WIDTH	15
#define BOOMERANG_BBOX_HEIGHT	15

#define BOOMERANG_SPEED_X		0.12f
#define BOOMERANG_LEAVE_TIME	1000


class CBoomerang :
	public CWeapon
{
	DWORD leaveStart;
	bool isReturned;
public:
	CBoomerang(D3DXVECTOR2 position, int nx);
	~CBoomerang();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
};

