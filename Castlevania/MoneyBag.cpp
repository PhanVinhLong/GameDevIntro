#include "MoneyBag.h"

CMoneyBag::CMoneyBag(D3DXVECTOR2 position, int id)
{
	this->x = position.x;
	this->y = position.y;
	this->id = id;

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

	AddAnimation(0);
}

CMoneyBag::~CMoneyBag()
{
}

void CMoneyBag::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void CMoneyBag::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
}

void CMoneyBag::Render()
{
}
