#pragma once
#include "GameObject.h"

#define PORTAL_BBOX_WIDTH	30
#define PORTAL_BBOX_HEIGHT	30

class CPortal :
	public CGameObject
{
private:
	D3DXVECTOR2 destination;
public:
	CPortal(D3DXVECTOR2 position, D3DXVECTOR2 destination);
	~CPortal();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};

typedef CPortal* LPPORTAL;