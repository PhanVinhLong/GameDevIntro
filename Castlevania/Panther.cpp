#include "Panther.h"

CPanther::CPanther(D3DXVECTOR2 position, int nx, int nextItemId)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	this->nextItemId = nextItemId;
	id = ID_PANTHER;

	AddAnimation(ID_ANI_PANTHER_IDLE_RIGHT);
	AddAnimation(ID_ANI_PANTHER_IDLE_LEFT);
	AddAnimation(ID_ANI_PANTHER_RUN_RIGHT);
	AddAnimation(ID_ANI_PANTHER_RUN_LEFT);
	AddAnimation(ID_ANI_PANTHER_JUMP_RIGHT);
	AddAnimation(ID_ANI_PANTHER_JUMP_LEFT);

	state = ENEMY_STATE_IDLE;
	score = 200;
	isOnGround = true;
	currentFloor = NULL;
}

CPanther::~CPanther()
{
}

void CPanther::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt, objects);

	vector<LPGAMEOBJECT> wallObjects;

	for (int i = 0; i < objects->size(); i++)
	{
		switch (objects->at(i)->GetId())
		{
		case ID_WALL:
			wallObjects.push_back(objects->at(i));
			break;
		}
	}

	// collision with wall
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision
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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		y += min_ty * dy + ny * 0.1f;

		if (ny < 0)
		{
			vy = 0;
			if (!isOnGround)
			{
				vx = -vx;
				nx = -nx;
				isOnGround = true;
				state = ENEMY_STATE_ACTIVE;
			}
			currentFloor = dynamic_cast<CWall*>(coEventsResult.back()->obj);
		}
		else y += dy;
		x += dx;
	}

	// clean up collision events
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// fall down
	if(state != ENEMY_STATE_ON_FIRE && stopWatchStart == 0)
		vy += PANTHER_GRAVITY * dt;

	// check active condition
	if (state == ENEMY_STATE_IDLE)
	{
		float sl, st, sr, sb, pl, pt, pr, pb;
		CSimon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
		GetBoundingBox(pl, pt, pr, pb);
		if (abs(pl - sr) < 40 || abs(sl - pr) < 40)
		{
			if (int((sb - HUD_HEIGHT) / 176) == int((pb - HUD_HEIGHT) / 176))
			{
				state = ENEMY_STATE_ACTIVE;
				vx = -nx * PANTHER_SPEED_X;
				isOnGround = false;
			}
		}
	}

	// check jump condition
	if (isOnGround && currentFloor && state == ENEMY_STATE_ACTIVE)
	{
		float fl, ft, fr, fb, pl, pt, pr, pb;
		currentFloor->GetBoundingBox(fl, ft, fr, fb);
		GetBoundingBox(pl, pt, pr, pb);
		if ((pl < fl && fl - pl < 2) || (pr > fr && pr - fr < 2))
		{
			vy = -PANTHER_JUMP_SPEED_Y;
			state = PANTHER_STATE_JUMP;
			isOnGround = false;
		}
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

void CPanther::Render()
{
	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_IDLE:
		if (nx > 0)
			ani = PANTHER_ANI_IDLE_RIGHT;
		else
			ani = PANTHER_ANI_IDLE_LEFT;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = PANTHER_ANI_RUN_RIGHT;
		else
			ani = PANTHER_ANI_RUN_LEFT;
		break;
	case ENEMY_STATE_ON_FIRE:
		ani = ENEMY_ANI_ON_FIRE;
		break;
	case PANTHER_STATE_JUMP:
		if (nx > 0)
			ani = PANTHER_ANI_JUMP_RIGHT;
		else
			ani = PANTHER_ANI_JUMP_LEFT;
		break;
	default:
		break;
	}
	if (stopWatchStart > 0 && state != ENEMY_STATE_ON_FIRE)
		animations[ani]->RenderFrame(x, y);
	else
		animations[ani]->Render(x, y);
}

void CPanther::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state != ENEMY_STATE_ON_FIRE)
	{
		left = x;
		top = y - PANTHER_BBOX_HEIGHT;
		right = x + PANTHER_BBOX_WIDTH;
		bottom = y;
	}
	else
		left = top = right = bottom = 0;
}
