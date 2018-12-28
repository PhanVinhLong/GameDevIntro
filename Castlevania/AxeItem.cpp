#include "AxeItem.h"

CAxeItem::CAxeItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_AXE;
	AddAnimation(ID_ANI_AXE_ITEM);
}

CAxeItem::~CAxeItem()
{
}

void CAxeItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - AXE_ITEM_BBOX_HEIGHT;
	r = x + AXE_ITEM_BBOX_WIDTH;
	b = y;
}

void CAxeItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy += AXE_ITEM_GRAVITY * dt;
}
