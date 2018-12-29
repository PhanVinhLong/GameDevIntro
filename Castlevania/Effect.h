#pragma once
#include "GameObject.h"

#define EFFECT_GRAVITY		0.00025f

#define EFFECT_ALIVE_TIME	2000

class CEffect :
	public CGameObject
{
protected:
	int num;
	float* x;
	float* y;
	float* vx;
	float* vy;

	DWORD startAlive;
public:
	CEffect();
	~CEffect();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
};

