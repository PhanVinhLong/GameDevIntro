#include "Dagger.h"

CDagger::CDagger(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y - 15;
	this->nx = nx;
	id = ID_DAGGER;
	vx = DAGGER_SPEED;
	AddAnimation(302);
	AddAnimation(303);
}

CDagger::~CDagger()
{
}

void CDagger::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - DAGGER_BBOX_HEIGHT;
	r = x + DAGGER_BBOX_WIDTH;
	b = y;
}

void CDagger::Render()
{
	int ani;
	ani = nx > 0 ? 0 : 1;
	animations[ani]->Render(x, y);
}

void CDagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (nx > 0)
		x += DAGGER_SPEED * dt;
	else
		x -= DAGGER_SPEED * dt;
	CWeapon::Update(dt, coObjects);
}
