#include "MapSet.h"

CMapSet::CMapSet(D3DXVECTOR2 position, int wBegin, int wEnd)
{
	this->x = position.x;
	this->y = position.y;
	this->wBegin = wBegin;
	this->wEnd = wEnd;
	id = ID_MAPSET;
}

CMapSet::~CMapSet()
{
}

void CMapSet::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - MAPSET_BBOX_HEIGHT;
	r = x + MAPSET_BBOX_WIDTH;
	b = y;
}

void CMapSet::Render()
{
}
