#pragma once
#include "GameObject.h"
#include "SmallHeart.h"
#include "LargeHeart.h"
#include "DaggerItem.h"
#include "WhipUpgrade.h"
#include "AxeItem.h"
#include "HolyWaterPotion.h"
#include "CrossItem.h"
#include "define.h"

#define GROUND_OBJ_ON_FIRE_TIME		450

#define GROUND_OBJ_STATE_NORMAL		0
#define GROUND_OBJ_STATE_ON_FIRE	1

class CGroundObject :
	public CGameObject
{
	DWORD onFireStart;
public:
	CGroundObject();
	~CGroundObject();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void BeDamaged();
};

