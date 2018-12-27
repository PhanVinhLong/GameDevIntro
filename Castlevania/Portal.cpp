#include "Portal.h"

CPortal::CPortal(D3DXVECTOR2 position, D3DXVECTOR2 destination)
{
	this->x = position.x;
	this->y = position.y;
	this->destination.x = destination.x;
	this->destination.y = destination.y + HUD_HEIGHT;
	id = ID_PORTAL;
}

CPortal::~CPortal()
{
}

void CPortal::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - PORTAL_BBOX_HEIGHT;
	r = x + PORTAL_BBOX_WIDTH;
	b = y;
}

void CPortal::Render()
{
	//
}

D3DXVECTOR2 CPortal::GetDestination()
{
	return destination;
}
