#pragma once
#include "TransparentObject.h"
class CStair :
	public CTransparentObject
{
	int bbWidth;
	int bbHeight;
	int height;
public:
	CStair(D3DXVECTOR2 position, int bbWidth, int bbHeight, int height, int nx, int ny);
	~CStair();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);

	int GetStairHeight() { return height; }

	int GetOriginX() { return (x + bbWidth / 2); }
};

