#include "Effect.h"

CEffect::CEffect()
{
	startAlive = GetTickCount();
}

CEffect::~CEffect()
{
}

void CEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	for (int i = 0; i < num; i++)
	{
		x[i] += vx[i] * dt;
		y[i] += vy[i] * dt;
		vy[i] += EFFECT_GRAVITY * dt;
	}

	if (GetTickCount() - startAlive > EFFECT_ALIVE_TIME)
		state = STATE_DESTROYED;
}

void CEffect::Render()
{
	for (int i = 0; i < num; i++)
	{
		animations[0]->Render(x[i], y[i]);
	}
}
