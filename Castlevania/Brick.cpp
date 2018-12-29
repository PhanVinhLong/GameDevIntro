#include "Brick.h"

CBrick::CBrick(D3DXVECTOR2 position, int nextItemTypeID)
{
	x = position.x;
	y = position.y;
	state = GROUND_OBJ_STATE_NORMAL;
	isBroken = false;
	id = ID_BRICK;
	this->nextItemId = nextItemTypeID;

	AddAnimation(ID_ANI_BRICK);
}

CBrick::~CBrick()
{
}

void CBrick::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state == GROUND_OBJ_STATE_NORMAL)
	{
		l = x;
		t = y - BRICK_BBOX_HEIGHT;
		r = x + BRICK_BBOX_WIDTH;
		b = y;
	}
	else
		l = t = r = b = 0;
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	if (!isBroken && state == GROUND_OBJ_STATE_ON_FIRE)
	{
		isBroken = true;

		CGameObject* nextItem;
		switch (GetNextItemId())
		{
		case ID_ITEM_SMALL_HEART:
			nextItem = new CSmallHeart({ x, y });
			break;
		case ID_ITEM_LARGE_HEART:
			nextItem = new CLargeHeart({ x, y });
			break;
		case ID_ITEM_WHIP_UPGRADE:
			nextItem = new CWhipUpgrade({ x, y });
			break;
		case ID_ITEM_DAGGER:
			nextItem = new CDaggerItem({ x, y });
			break;
		case ID_ITEM_AXE:
			nextItem = new CAxeItem({ x, y });
			break;
		case ID_ITEM_STOPWATCH:
			nextItem = new CStopwatchItem({ x, y });
			break;
		case ID_ITEM_BOOMERANG:
			nextItem = new CBoomerangItem({ x, y });
			break;
		case ID_ITEM_HOLY_WATER:
			nextItem = new CHolyWaterPotion({ x , y });
			break;
		case ID_ITEM_CROSS:
			nextItem = new CCrossItem({ x, y });
			break;
		case ID_ITEM_INVINCIBILITY_POTION:
			nextItem = new CInvincibilityPotion({ x, y });
			break;
		case ID_MONEY_BAG_RED:
		case ID_MONEY_BAG_PURPLE:
		case ID_MONEY_BAG_WHITE:
		case ID_MONEY_BAG_BONUS:
			nextItem = new CMoneyBag({ x, y }, GetNextItemId());
			break;
		case ID_DOUBLE_SHOOT:
		case ID_TRIPLE_SHOOT:
			nextItem = new CMultiShootItem({ x, y }, GetNextItemId());
			break;
		case ID_POT_ROAST:
			nextItem = new CPotRoast({ x, y });
			break;
		default:
			nextItem = NULL;
			break;
		}
		if (nextItem)
			objects->push_back(nextItem);

		float ox, oy;
		GetPosition(ox, oy);
		CBrickEffect* effect = new CBrickEffect({ ox, oy });
		objects->push_back(effect);
	}
}

void CBrick::Render()
{
	if (state != GROUND_OBJ_STATE_NORMAL)
		animations[1]->Render(x, y);
}

void CBrick::BeDamaged()
{
	state = GROUND_OBJ_STATE_ON_FIRE;
}
