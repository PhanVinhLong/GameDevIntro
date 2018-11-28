#include "WhipUpgrade.h"

CWhipUpgrade::CWhipUpgrade(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_WHIP_UPGRADE;
	AddAnimation(301);
}

CWhipUpgrade::~CWhipUpgrade()
{
}

void CWhipUpgrade::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - WHIP_UPGRADE_BBOX_HEIGHT;
	r = x + WHIP_UPGRADE_BBOX_WIDTH;
	b = y;
}

void CWhipUpgrade::Render()
{
	animations[0]->Render(x, y);
}

void CWhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += WHIP_UPGRADE_GRAVITY * dt;

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
