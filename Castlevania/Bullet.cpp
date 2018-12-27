#include "Bullet.h"

CBullet::CBullet(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y;
	this->nx = nx;

	id = ID_BULLET;
	vx = nx * BULLET_SPEED_X;
	state = ENEMY_STATE_ACTIVE;

	AddAnimation(ID_ANI_BULLET_RIGHT);
	AddAnimation(ID_ANI_BULLET_LEFT);
}

CBullet::~CBullet()
{
}

void CBullet::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - BULLET_BBOX_HEIGHT;
	r = x + BULLET_BBOX_WIDTH;
	b = y;
}

void CBullet::Render()
{
	int ani;
	ani = nx > 0 ? 1 : 2;
	if (state == ENEMY_STATE_ON_FIRE)
		ani = 0;
	animations[ani]->Render(x, y);
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CEnemy::Update(dt, objects);
}
