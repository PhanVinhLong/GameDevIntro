#include "Boomerang.h"

CBoomerang::CBoomerang(D3DXVECTOR2 position, int nx)
{
	x = position.x;
	y = position.y - 15;
	this->nx = nx;
	id = ID_SUBWEAPON_BOOMERANG;
	vx = nx * BOOMERANG_SPEED_X;
	leaveStart = GetTickCount();
	isReturned = false;

	AddAnimation(ID_ANI_BOOMERANG_RIGHT);
	AddAnimation(ID_ANI_BOOMERANG_LEFT);
}

CBoomerang::~CBoomerang()
{
}

void CBoomerang::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - BOOMERANG_BBOX_HEIGHT;
	r = x + BOOMERANG_BBOX_WIDTH;
	b = y;
}

void CBoomerang::Render()
{
	int ani;
	ani = nx > 0 ? 0 : 1;
	animations[ani]->Render(x, y);
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CWeapon::Update(dt, objects);

	if (leaveStart > 0 && GetTickCount() - leaveStart > BOOMERANG_LEAVE_TIME)
	{
		leaveStart = 0;
		nx = -nx;
		vx = -vx;
		isReturned = true;
	}
	if (isReturned)
	{
		float sl, st, sr, sb, l, t, r, b;
		GetBoundingBox(l, t, r, b);

		// delete when out of viewport
		CSimon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
		if (CGame::IsIntersect({ (long)sl, (long)st, (long)sr, (long)sb },
			{ (long)l, (long)t, (long)r, (long)b }))
			state = STATE_DESTROYED;
	}
}
