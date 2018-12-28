#pragma once
#include "Item.h"

#define INVINCIBILITY_POTION_GRAVITY			0.0005f
#define INVINCIBILITY_POTION_BBOX_WIDTH			15
#define INVINCIBILITY_POTION_BBOX_HEIGHT		15

class CInvincibilityPotion :
	public CItem
{
public:
	CInvincibilityPotion(D3DXVECTOR2 position);
	~CInvincibilityPotion();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

