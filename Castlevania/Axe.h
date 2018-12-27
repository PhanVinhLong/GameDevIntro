#pragma once
#include "Weapon.h"

#define AXE_BBOX_WIDTH		16
#define AXE_BBOX_HEIGHT		16

#define AXE_SPEED_X			0.09f
#define AXE_GRAVITY			0.0004f
#define AXE_THROW_SPEED_Y	0.22f

class CAxe :
	public CWeapon
{
public:
	CAxe(D3DXVECTOR2 position, int nx);
	~CAxe();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

