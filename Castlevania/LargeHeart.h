#pragma once
#include "GameObject.h"

#define LARGE_HEART_GRAVITY			0.0005f
#define LARGE_HEART_BBOX_WIDTH		13
#define LARGE_HEART_BBOX_HEIGHT		10

class CLargeHeart :
	public CGameObject
{
public:
	CLargeHeart(D3DXVECTOR2 position);
	~CLargeHeart();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

typedef CLargeHeart* LPLARGEHEART;