#include "Enemy.h"

CEnemy::CEnemy()
{
	AddAnimation(ID_ANI_ENEMY_ON_FIRE);

	onFireStart = 0;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);

	vector<LPGAMEOBJECT> wallObjects;

	for (int i = 0; i < objects->size(); i++)
		if (objects->at(i)->GetId() == ID_WALL)
			wallObjects.push_back(objects->at(i));

	// collision with wall
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision
	CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		if (stopWatchStart == 0)
		{
			x += dx;
			y += dy;
		}
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		int idx, idy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		x += min_tx * dx + nx * 0.11f;		// nx*0.1f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.10f;

		if (ny < 0)
		{
			vy = 0;
			if (!isOnGround) isOnGround = true;
		}
		else if(stopWatchStart == 0) y += dy;
		if (stopWatchStart == 0)x += dx;
	}

	// clean up collision events
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	if (GetTickCount() - onFireStart > ENEMY_ON_FIRE_TIME && onFireStart > 0)
	{
		onFireStart = 0;
		state = STATE_DESTROYED;

		CGameObject* nextItem;
		switch (GetNextItemId())
		{
		case ID_ITEM_LARGE_HEART:
			nextItem = new CLargeHeart({ x, y });
			break;
		case ID_ITEM_WHIP_UPGRADE:
			nextItem = new CWhipUpgrade({ x, y });
			break;
		case ID_ITEM_DAGGER:
			nextItem = new CDaggerItem({ x, y });
			break;
		case ID_ITEM_SMALL_HEART:
			nextItem = new CSmallHeart({ x, y });
			break;
		default:
			nextItem = NULL;
			break;
		}
		if (nextItem)
			objects->push_back(nextItem);
	}

	// delete when out of screen
	float vl, vt, vr, vb, l, t, r, b;
	CViewport::GetInstance()->GetBoundingBox(vl, vt, vr, vb);
	GetBoundingBox(l, t, r, b);
	if (!(CGame::IsIntersect({ (long)vl, (long)vt, (long)vr, (long)vb },
		{ (long)l, (long)t, (long)r, (long)b })) && state == ENEMY_STATE_ACTIVE)
		state = STATE_DESTROYED;
}

void CEnemy::BeDamaged()
{
	SetSpeed(0, 0);
	CSimon::GetInstance()->AddScore(score);
	onFireStart = GetTickCount();
	state = ENEMY_STATE_ON_FIRE;
}
