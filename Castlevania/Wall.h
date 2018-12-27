#pragma once
#include "GameObject.h"
class CWall :
	public CGameObject
{
	int width;
	int height;
public:
	CWall();
	CWall(D3DXVECTOR2 position, int width, int height);
	~CWall();

	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};
