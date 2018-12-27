#include "HolyWaterPotion.h"

CHolyWaterPotion::CHolyWaterPotion(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_HOLY_WATER;
	AddAnimation(ID_ANI_HOLY_WATER_ITEM);
}

CHolyWaterPotion::~CHolyWaterPotion()
{
}

void CHolyWaterPotion::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - HOLY_WATER_ITEM_BBOX_HEIGHT;
	r = x + HOLY_WATER_ITEM_BBOX_WIDTH;
	b = y;
}

void CHolyWaterPotion::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy += HOLY_WATER_ITEM_GRAVITY * dt;
}
