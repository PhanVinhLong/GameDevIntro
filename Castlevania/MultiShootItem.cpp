#include "MultiShootItem.h"

CMultiShootItem::CMultiShootItem(D3DXVECTOR2 position, int id)
{
	x = position.x;
	y = position.y;
	this->id = id;
	AddAnimation(ID_ANI_DOUBLE_SHOOT_ITEM);
	AddAnimation(ID_ANI_TRIPLE_SHOOT_ITEM);
}

CMultiShootItem::~CMultiShootItem()
{
}

void CMultiShootItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - MULTI_SHOOT_ITEM_BBOX_HEIGHT;
	r = x + MULTI_SHOOT_ITEM_BBOX_WIDTH;
	b = y;
}

void CMultiShootItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy += MULTI_SHOOT_ITEM_GRAVITY * dt;
}
