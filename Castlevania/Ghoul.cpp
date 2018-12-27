#include "Ghoul.h"

CGhoul::CGhoul(D3DXVECTOR2 postition, int nx, int nextItemId)
{
	x = postition.x;
	y = postition.y;
	this->nx = nx;
	this->nextItemId = nextItemId;
	score = 200;
	vx = nx * GHOUL_SPEED_X;
	state = ENEMY_STATE_ACTIVE;

	id = ID_GHOUL;

	AddAnimation(ID_ANI_GHOUL_WALK_RIGHT);
	AddAnimation(ID_ANI_GHOUL_WALK_LEFT);
}

CGhoul::~CGhoul()
{
}

void CGhoul::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CEnemy::Update(dt, objects);

	// fall down
	if (state != ENEMY_STATE_ON_FIRE)
		vy += GHOUL_GRAVITY * dt;
}

void CGhoul::Render()
{
	int ani = 0;
	switch (state)
	{
	case ENEMY_STATE_ACTIVE:
		if (nx > 0)
			ani = GHOUL_ANI_WALK_RIGHT;
		else
			ani = GHOUL_ANI_WALK_LEFT;
		break;
	case ENEMY_STATE_ON_FIRE:
		ani = ENEMY_ANI_ON_FIRE;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void CGhoul::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == ENEMY_STATE_ACTIVE)
	{
		left = x;
		top = y - GHOUL_BBOX_HEIGHT;
		right = x + GHOUL_BBOX_WIDTH;
		bottom = y;
	}
	else
		left = top = right = bottom = 0;
}
