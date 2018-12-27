#include "DaggerItem.h"

CDaggerItem::CDaggerItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_DAGGER;
	AddAnimation(ID_ANI_DAGGER_ITEM);
}

CDaggerItem::~CDaggerItem()
{
}

void CDaggerItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - DAGGER_ITEM_BBOX_HEIGHT;
	r = x + DAGGER_ITEM_BBOX_WIDTH;
	b = y;
}

void CDaggerItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if(!isOnGround)
		vy += DAGGER_ITEM_GRAVITY * dt;
}
