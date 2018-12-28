#include "StopwatchItem.h"

CStopwatchItem::CStopwatchItem(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_STOPWATCH;
	AddAnimation(ID_ANI_STOPWATCH_ITEM);
}

CStopwatchItem::~CStopwatchItem()
{
}

void CStopwatchItem::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - STOPWATCH_ITEM_BBOX_HEIGHT;
	r = x + STOPWATCH_ITEM_BBOX_WIDTH;
	b = y;
}

void CStopwatchItem::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += STOPWATCH_ITEM_GRAVITY * dt;
}
