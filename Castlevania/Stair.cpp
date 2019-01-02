#include "Stair.h"

CStair::CStair(D3DXVECTOR2 position, int bbWidth, int bbHeight, int height, int nx, int ny)
{
	x = position.x;
	y = position.y;
	this->bbWidth = bbWidth;
	this->bbHeight = bbHeight;
	this->height = height;
	this->nx = nx;
	this->ny = ny;

	id = ID_STAIR;
}

CStair::~CStair()
{
}

void CStair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - bbHeight;
	r = x + bbWidth;
	b = y;
}
