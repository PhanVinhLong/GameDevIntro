#include "Water.h"



CWater::CWater()
{
}

CWater::CWater(D3DXVECTOR2 position, int width, int height)
{
	this->width = width;
	this->height = height;
	this->x = position.x;
	this->y = position.y;
	id = ID_WATER;
}


CWater::~CWater()
{
}

void CWater::Render()
{
}

void CWater::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - height;
	r = x + width;
	b = y;
}
