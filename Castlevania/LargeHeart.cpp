#include "LargeHeart.h"

CLargeHeart::CLargeHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;
	AddAnimation(300);
	id = ID_LARGE_HEART;
}

CLargeHeart::~CLargeHeart()
{
}

void CLargeHeart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - LARGE_HEART_BBOX_HEIGHT;
	r = x + LARGE_HEART_BBOX_WIDTH;
	b = y;
}

void CLargeHeart::Render()
{
	animations[0]->Render(x, y);
}

void CLargeHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += LARGE_HEART_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 1; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetID() == ID_WALL)
			wallObjects.push_back(coObjects->at(i));

	// turn off collision when die 
	CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		int idx, idy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, idx, idy);

		// block 
		x += min_tx * dx + nx * 0.1f;		// nx*0.1f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}
