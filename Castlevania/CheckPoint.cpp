#include "CheckPoint.h"

CCheckPoint::CCheckPoint(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_CHECK_POINT;
}

CCheckPoint::~CCheckPoint()
{
}

void CCheckPoint::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - CHECKPOINT_BBOX_HEIGHT;
	r = x + CHECKPOINT_BBOX_WIDTH;
	b = y;
}

void CCheckPoint::Render()
{
}
