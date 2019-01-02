#pragma once
#include "GameObject.h"
class CTransparentObject :
	public CGameObject
{
public:
	CTransparentObject();
	~CTransparentObject();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

