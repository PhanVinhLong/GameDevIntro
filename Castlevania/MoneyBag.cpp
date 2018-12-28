#include "MoneyBag.h"

CMoneyBag::CMoneyBag(D3DXVECTOR2 position, int id)
{
	this->x = position.x;
	this->y = position.y;
	this->id = id;

	showScoreStart = 0;

	switch (id)
	{
	case ID_MONEY_BAG_RED:
		score = 100;
		break;
	case ID_MONEY_BAG_PURPLE:
		score = 400;
		break;
	case ID_MONEY_BAG_WHITE:
		score = 700;
		break;
	case ID_MONEY_BAG_BONUS:
		score = 1000;
	default:
		break;
	}

	AddAnimation(ID_ANI_MONEY_BAG_RED);
	AddAnimation(ID_ANI_MONEY_BAG_RED_SCORE);
	AddAnimation(ID_ANI_MONEY_BAG_PURPLE);
	AddAnimation(ID_ANI_MONEY_BAG_PURPLE_SCORE);
	AddAnimation(ID_ANI_MONEY_BAG_WHITE);
	AddAnimation(ID_ANI_MONEY_BAG_WHITE_SCORE);
	AddAnimation(ID_ANI_MONEY_BAG_BONUS);
	AddAnimation(ID_ANI_MONEY_BAG_BONUS_SCORE);
}

CMoneyBag::~CMoneyBag()
{
}

void CMoneyBag::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (showScoreStart == 0)
	{
		l = x;
		t = y - MONEY_BAG_BBOX_HEIGHT;
		r = x + MONEY_BAG_BBOX_WIDTH;
		b = y;
	}
	else
		l = t = r = b = 0;
}

void CMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += MONEY_BAG_GRAVITY * dt;
	if (showScoreStart > 0)
		vy = 0;

	if (showScoreStart > 0 && GetTickCount() - showScoreStart > MONEY_BAG_SHOW_SCORE_TIME)
		state = STATE_DESTROYED;
}

void CMoneyBag::Render()
{
	int ani = 0;
	switch (id)
	{
	case ID_MONEY_BAG_RED:
		if (showScoreStart == 0)
			ani = MONEY_BAG_RED_ANI;
		else
			ani = MONEY_BAG_RED_SCORE_ANI;
		break;
	case ID_MONEY_BAG_PURPLE:
		if (showScoreStart == 0)
			ani = MONEY_BAG_PURPLE_ANI;
		else
			ani = MONEY_BAG_PURPLE_SCORE_ANI;
		break;
	case ID_MONEY_BAG_WHITE:
		if (showScoreStart == 0)
			ani = MONEY_BAG_WHITE_ANI;
		else
			ani = MONEY_BAG_WHITE_SCORE_ANI;
		break;
	case ID_MONEY_BAG_BONUS:
		if (showScoreStart == 0)
			ani = MONEY_BAG_BONUS_ANI;
		else
			ani = MONEY_BAG_BONUS_SCORE_ANI;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void CMoneyBag::StartShowScore()
{
	showScoreStart = GetTickCount();
}
