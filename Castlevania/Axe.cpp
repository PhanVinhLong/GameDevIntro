#include "Axe.h"

CAxe::CAxe(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y - 15;
	this->nx = nx;
	vy = -AXE_THROW_SPEED_Y;
	id = ID_SUBWEAPON_AXE;
	vx = AXE_SPEED_X;

	AddAnimation(ID_ANI_AXE_RIGHT);
	AddAnimation(ID_ANI_AXE_LEFT);
}

CAxe::~CAxe()
{
}

void CAxe::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - AXE_BBOX_HEIGHT;
	r = x + AXE_BBOX_WIDTH;
	b = y; 
}

void CAxe::Render()
{
	int ani;
	ani = nx > 0 ? 0 : 1;
	animations[ani]->Render(x, y);
}

void CAxe::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	vx = nx * AXE_SPEED_X;
	vy += AXE_GRAVITY * dt;

	CWeapon::Update(dt, objects);
}
