#pragma once
#include "Item.h"

#define MONEY_BAG_GRAVITY				0.0005f
#define MONEY_BAG_BBOX_WIDTH			20
#define MONEY_BAG_BBOX_HEIGHT			20

#define MONEY_BAG_RED_ANI				0
#define MONEY_BAG_RED_SCORE_ANI			1
#define MONEY_BAG_PURPLE_ANI			2
#define MONEY_BAG_PURPLE_SCORE_ANI		3
#define MONEY_BAG_WHITE_ANI				4
#define MONEY_BAG_WHITE_SCORE_ANI		5
#define MONEY_BAG_BONUS_ANI				6
#define MONEY_BAG_BONUS_SCORE_ANI		7

#define MONEY_BAG_SHOW_SCORE_TIME		1200

class CMoneyBag :
	public CItem
{
	DWORD showScoreStart;
public:
	CMoneyBag(D3DXVECTOR2 position, int id);
	~CMoneyBag();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *objects);
	virtual void Render();
	void StartShowScore();
};

