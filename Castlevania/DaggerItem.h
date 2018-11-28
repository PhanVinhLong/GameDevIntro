#pragma once
#include "GameObject.h"

#define DAGGER_ITEM_GRAVITY			0.0005f
#define DAGGER_ITEM_BBOX_WIDTH		15
#define DAGGER_ITEM_BBOX_HEIGHT		15

class CDaggerItem :
	public CGameObject
{
public:
	CDaggerItem(D3DXVECTOR2 position);
	~CDaggerItem();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CDaggerItem* LPDAGGERITEM;