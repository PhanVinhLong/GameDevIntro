#include "PotRoast.h"

CPotRoast::CPotRoast(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	this->id = ID_POT_ROAST;
	AddAnimation(ID_ANI_POT_ROAST_ITEM);
}

CPotRoast::~CPotRoast()
{
}

void CPotRoast::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y -POT_ROAST_ITEM_BBOX_HEIGHT;
	r = x +POT_ROAST_ITEM_BBOX_WIDTH;
	b = y;
}

void CPotRoast::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy +=POT_ROAST_ITEM_GRAVITY * dt;
}
