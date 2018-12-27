#pragma once
#include "GameObject.h"

#define ITEM_DISAPPEAR_TIME		5000
class CItem :
	public CGameObject
{
	DWORD disappearStart;
public:
	CItem();
	~CItem();

	void StartDisappear();

	virtual void GetBoundingBox(float &l, float &t, float &r, float &b) = 0;
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
};

