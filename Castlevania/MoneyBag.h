#pragma once
#include "Item.h"

#define LARGE_HEART_GRAVITY				0.0005f
#define LARGE_HEART_BBOX_WIDTH			20
#define LARGE_HEART_BBOX_HEIGHT			20

#define MONEY_BAG_RED_ANI				0
#define MONEY_BAG_RED_SCORE_ANI			1
#define MONEY_BAG_PURPLE_ANI			2
#define MONEY_BAG_PURPLE_SCORE_ANI		3
#define MONEY_BAG_WHITE_ANI				4
#define MONEY_BAG_WHITE_SCORE_ANI		5
#define MONEY_BAG_BONUS_ANI				6
#define MONEY_BAG_BONUS_SCORE_ANI		7

class CMoneyBag :
	public CItem
{
public:
	CMoneyBag(D3DXVECTOR2 position, int id);
	~CMoneyBag();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
	virtual void Render();

};

