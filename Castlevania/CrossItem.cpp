#include "CrossItem.h"

CCrossItem::CCrossItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_CROSS;
	AddAnimation(ID_ANI_CROSS_ITEM);
}

CCrossItem::~CCrossItem()
{
}

void CCrossItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - CROSS_ITEM_BBOX_HEIGHT;
	r = x + CROSS_ITEM_BBOX_WIDTH;
	b = y;
}

void CCrossItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy += CROSS_ITEM_GRAVITY * dt;
}
