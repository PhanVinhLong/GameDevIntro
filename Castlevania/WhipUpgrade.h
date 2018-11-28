#pragma once
#include "GameObject.h"

#define WHIP_UPGRADE_GRAVITY		0.0005f
#define WHIP_UPGRADE_BBOX_WIDTH		20
#define WHIP_UPGRADE_BBOX_HEIGHT	20

class CWhipUpgrade :
	public CGameObject
{
public:
	CWhipUpgrade(D3DXVECTOR2 position);
	~CWhipUpgrade();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

