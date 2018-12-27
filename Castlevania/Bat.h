#pragma once
#include "Enemy.h"

#define BAT_SPEED_X				0.07f

#define BAT_BBOX_WIDTH			18
#define BAT_BBOX_HEIGHT			16

#define BAT_ANI_FLY_RIGHT		1
#define BAT_ANI_FLY_LEFT		2

class CBat :
	public CEnemy
{
	int originY;
	int delta;
public:
	CBat(D3DXVECTOR2 postition, int nx, int nextItemId);
	~CBat();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

