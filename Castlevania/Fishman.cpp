#include "Fishman.h"

CFishman::CFishman(D3DXVECTOR2 position, int nx, int nextItemId)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	this->nextItemId = nextItemId;
	id = ID_FISHMAN;

	AddAnimation(ID_ANI_FISHMAN_IDLE_RIGHT);
	AddAnimation(ID_ANI_FISHMAN_IDLE_LEFT);
	AddAnimation(ID_ANI_FISHMAN_WALK_RIGHT);
	AddAnimation(ID_ANI_FISHMAN_WALK_LEFT);
	AddAnimation(ID_ANI_FISHMAN_ATTACK_RIGHT);
	AddAnimation(ID_ANI_FISHMAN_ATTACK_LEFT);

	state = ENEMY_STATE_IDLE;
	vx = 0;
	vy = -FISHMAN_JUMP_SPEED_Y;
	score = 200;
	isOnGround = false;

	isShowedEffect = false;
}

CFishman::~CFishman()
{

}

void CFishman::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CEnemy::Update(dt, objects);

	if(state != ENEMY_STATE_ON_FIRE)
		vy += FISHMAN_GRAVITY * dt;

	if (isOnGround && state == ENEMY_STATE_IDLE)
	{
		state = ENEMY_STATE_ACTIVE;
		vx = nx * FISHMAN_SPEED_X;
		activeStart = GetTickCount();
	}

	if (activeStart && GetTickCount() - activeStart > FISHMAN_ACTIVE_TIME)
	{
		activeStart = 0;
		if (state != ENEMY_STATE_ON_FIRE)
		{
			CBullet* bullet = new CBullet({ x, y - 23 }, nx);
			objects->push_back(bullet);
			SetState(FISHMAN_STATE_ATTACK);
		}
	}
	if (attackStart && GetTickCount() - attackStart > FISHMAN_ATTACK_TIME)
	{
		attackStart = 0;
		SetState(ENEMY_STATE_ACTIVE);
	}

	if (!isShowedEffect)
	{
		CWaterEffect* waterEffect = new CWaterEffect({ x, y });
		objects->push_back(waterEffect);
		isShowedEffect = true;
	}

	// colision
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// collision with item
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(objects, coEvents);
	for (auto iter : coEvents)
		ColideWithObject(iter->obj, objects);
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
	{
		for (auto iter : *objects)
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (CGame::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) },
				{ long(bl), long(bt), long(br), long(bb) }))
				ColideWithObject(iter, objects);
		}
	}
}

void CFishman::Render()
{
	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_IDLE:
		if (nx > 0)
			ani = FISHMAN_ANI_IDLE_RIGHT;
		else
			ani = FISHMAN_ANI_IDLE_LEFT;
		break;
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = FISHMAN_ANI_WALK_RIGHT;
		else
			ani = FISHMAN_ANI_WALK_LEFT;
		break;
	case ENEMY_STATE_ON_FIRE:
		ani = ENEMY_ANI_ON_FIRE;
		break;
	case FISHMAN_STATE_ATTACK:
		if (nx > 0)
			ani = FISHMAN_ANI_ATTACK_RIGHT;
		else
			ani = FISHMAN_ANI_ATTACK_LEFT;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void CFishman::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state != ENEMY_STATE_ON_FIRE)
	{
		left = x;
		top = y - FISHMAN_BBOX_HEIGHT;
		right = x + FISHMAN_BBOX_WIDTH;
		bottom = y;
	}
	else
		left = top = right = bottom = 0;
}

void CFishman::ColideWithObject(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>* objects)
{
	switch (obj->GetId())
	{
	case ID_WATER:
	{
		CWaterEffect* waterEffect = new CWaterEffect({ x, y });
		objects->push_back(waterEffect);
		state = STATE_DESTROYED;
		break;
	}
	default:
		break;
	}
}

void CFishman::SetState(int state)
{
	if (GetState() == ENEMY_STATE_ON_FIRE)
		return;

	CGameObject::SetState(state);
	switch (state)
	{
	case ENEMY_STATE_ACTIVE:
		nx = -nx;
		vx = nx * FISHMAN_SPEED_X;
		activeStart = GetTickCount();
		break;
	case FISHMAN_STATE_ATTACK:
		vx = 0;
		attackStart = GetTickCount();
		break;
	default:
		break;
	}
}
