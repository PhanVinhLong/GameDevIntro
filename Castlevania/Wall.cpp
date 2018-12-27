#include "Wall.h"



CWall::CWall()
{
	width = 16;
	height = 16;
	x = 0;
	y = 0;
	id = ID_WALL;
}


CWall::CWall(D3DXVECTOR2 pos, int width, int height)
{
	this->width = width;
	this->height = height;
	this->x = pos.x;
	this->y = pos.y;
	id = ID_WALL;
}

CWall::~CWall()
{
}

void CWall::Render()
{
}

void CWall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - height;
	r = x + width;
	b = y;
}
