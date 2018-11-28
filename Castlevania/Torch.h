#pragma once
#include "GameObject.h"

#define TORCH_BBOX_WIDTH		18
#define TORCH_BBOX_HEIGHT		30

class CTorch :
	public CGameObject
{
private:

public:
	CTorch();
	CTorch(D3DXVECTOR2 position, int nextItemTypeID);
	~CTorch();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
};

typedef CTorch* LPTOUCH;
