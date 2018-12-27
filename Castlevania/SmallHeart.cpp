#include "SmallHeart.h"

CSmallHeart::CSmallHeart(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->originX = position.x;
	this->y = position.y;
	AddAnimation(ID_ANI_SMALL_HEART);
	id = ID_ITEM_SMALL_HEART;
	delta = 0;
}

CSmallHeart::~CSmallHeart()
{
}

void CSmallHeart::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - SMALL_HEART_BBOX_HEIGHT;
	r = x + SMALL_HEART_BBOX_WIDTH;
	b = y;
}

void CSmallHeart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isOnGround)
	{
		vy += SMALL_HEART_GRAVITY;
		delta += 2.5;
		x = sin(delta * 3.14 / 180) * 15 + originX;
	}

	CItem::Update(dt, coObjects);
}
