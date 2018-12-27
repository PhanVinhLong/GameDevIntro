#pragma once
#include "Enemy.h"

#define BULLET_BBOX_WIDTH	7
#define BULLET_BBOX_HEIGHT	6

#define BULLET_SPEED_X		0.08f

class CBullet :
	public CEnemy
{
public:
	CBullet(D3DXVECTOR2 position, int nx);
	~CBullet();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
};

