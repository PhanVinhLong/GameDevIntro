#pragma once
#include "GameObject.h"
#include "Game.h"
#include "LargeHeart.h"
#include "WhipUpgrade.h"
#include "DaggerItem.h"
#include "SmallHeart.h"

#define ID_SUBWEAPON_NONE	-1

class CWeapon :
	public CGameObject
{
public:
	CWeapon();
	~CWeapon();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CWeapon* LPWEAPON;