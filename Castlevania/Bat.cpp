#include "Bat.h"

CBat::CBat(D3DXVECTOR2 position, int nx, int nextItemId)
{
	this->x = position.x;
	this->y = position.y;
	this->nx = nx;
	this->nextItemId = nextItemId;

	this->originY = y;
	delta = 0;
	vx = nx * BAT_SPEED_X;
	state = ENEMY_STATE_ACTIVE;

	id = ID_BAT;

	AddAnimation(ID_ANI_BAT_FLY_RIGHT);
	AddAnimation(ID_ANI_BAT_FLY_LEFT);
}

CBat::~CBat()
{
}

void CBat::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CEnemy::Update(dt, objects);

	if (state != ENEMY_STATE_ON_FIRE)
	{
		delta += 3.7f;
		y = sin(delta * 3.14 / 180) * 12 + originY;
	}
}

void CBat::Render()
{
	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = BAT_ANI_FLY_RIGHT;
		else
			ani = BAT_ANI_FLY_LEFT;
		break;
	case ENEMY_STATE_ON_FIRE:
		ani = ENEMY_ANI_ON_FIRE;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void CBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == ENEMY_STATE_ACTIVE)
	{
		left = x;
		top = y - BAT_BBOX_HEIGHT;
		right = x + BAT_BBOX_WIDTH;
		bottom = y;
	}
	else
		left = top = right = bottom = 0;
}
