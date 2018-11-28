#include "DaggerItem.h"

CDaggerItem::CDaggerItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_DAGGER_ITEM;
	AddAnimation(302);
}

CDaggerItem::~CDaggerItem()
{
}

void CDaggerItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - DAGGER_ITEM_BBOX_HEIGHT;
	r = x + DAGGER_ITEM_BBOX_WIDTH;
	b = y;
}

void CDaggerItem::Render()
{
	animations[0]->Render(x, y);
}

void CDaggerItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += DAGGER_ITEM_GRAVITY * dt;

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
