#pragma once
#include "Enemy.h"

#define GHOUL_SPEED_X			0.027f	
#define GHOUL_GRAVITY			0.0006f

#define GHOUL_BBOX_WIDTH		15
#define GHOUL_BBOX_HEIGHT		30

#define GHOUL_ANI_WALK_RIGHT	1
#define GHOUL_ANI_WALK_LEFT		2


class CGhoul :
	public CEnemy
{
public:
	CGhoul(D3DXVECTOR2 postition, int nx, int nextItemId);
	~CGhoul();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

