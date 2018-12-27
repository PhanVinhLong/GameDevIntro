#pragma once
#include "Weapon.h"

#define HOLY_WATER_BBOX_WIDTH			8
#define HOLY_WATER_BBOX_HEIGHT			9
#define HOLY_WATER_BBOX_FIRED_WIDTH		16
#define HOLY_WATER_BBOX_FIRED_HEIGHT	12

#define HOLY_WATER_SPEED_X				0.09f
#define HOLY_WATER_GRAVITY				0.0004f
#define HOLY_WATER_THROW_SPEED_Y		0.12f

#define HOLY_WATER_FIRE_TIME			2000

class CHolyWater :
	public CWeapon
{
	DWORD fireStart;
public:
	CHolyWater(D3DXVECTOR2 position, int nx);
	~CHolyWater();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

