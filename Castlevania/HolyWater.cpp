#include "HolyWater.h"

CHolyWater::CHolyWater(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y - 15;
	fireStart = 0;
	this->nx = nx;
	vy = -HOLY_WATER_THROW_SPEED_Y;
	id = ID_SUBWEAPON_HOLY_WATER;
	vx = HOLY_WATER_SPEED_X;

	id = ID_SUBWEAPON_HOLY_WATER;

	AddAnimation(ID_ANI_HOLY_WATER_RIGHT);
	AddAnimation(ID_ANI_HOLY_WATER_LEFT);
	AddAnimation(ID_ANI_HOLY_WATER_FIRED);
}

CHolyWater::~CHolyWater()
{
}

void CHolyWater::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - HOLY_WATER_BBOX_HEIGHT;
	r = x + HOLY_WATER_BBOX_WIDTH;
	b = y;
	if (isOnGround)
	{
		t = y - HOLY_WATER_BBOX_FIRED_HEIGHT;
		r = x + HOLY_WATER_BBOX_FIRED_WIDTH;
	}
}

void CHolyWater::Render()
{
	int ani;
	if (!isOnGround)
		ani = nx > 0 ? 0 : 1;
	else
		ani = 2;

	RenderBoundingBox(100);
	animations[ani]->Render(x, y);
}

void CHolyWater::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - fireStart >= HOLY_WATER_FIRE_TIME && fireStart > 0)
		SetState(STATE_DESTROYED);

	if (!isOnGround)
	{
		vx = nx * HOLY_WATER_SPEED_X;
		vy += HOLY_WATER_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		vector<LPGAMEOBJECT> wallObjects;
		for (int i = 1; i < objects->size(); i++)
			if (objects->at(i)->GetId() == ID_WALL)
				wallObjects.push_back(objects->at(i));

		CalcPotentialCollisions(&wallObjects, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() != 0)
		{
			float min_tx, min_ty, nx = 0, ny;
			int idx, idy;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			// block 
			y += min_ty * dy + ny * 0.1f;

			if (ny != 0)
			{
				vx = 0;
				vy = 0;
				isOnGround = true;
				fireStart = GetTickCount();
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		coEvents.clear();
	}

	// clean up collision events

	CWeapon::Update(dt, objects);
}
