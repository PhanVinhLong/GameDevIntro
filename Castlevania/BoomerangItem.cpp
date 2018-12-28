#include "BoomerangItem.h"

CBoomerangItem::CBoomerangItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_BOOMERANG;
	AddAnimation(ID_ANI_BOOMERANG_ITEM);
}

CBoomerangItem::~CBoomerangItem()
{
}

void CBoomerangItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - BOOMERANG_ITEM_BBOX_HEIGHT;
	r = x + BOOMERANG_ITEM_BBOX_WIDTH;
	b = y;
}

void CBoomerangItem::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += BOOMERANG_ITEM_GRAVITY * dt;
}
