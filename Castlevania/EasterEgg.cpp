#include "EasterEgg.h"

CEasterEgg::CEasterEgg(D3DXVECTOR2 position, D3DXVECTOR2 destination, int nextItemId)
{
	this->x = position.x;
	this->y = position.y;
	this->destination = destination;
	this->nextItemId = nextItemId;

	id = ID_EASTER_EGG;
}

CEasterEgg::~CEasterEgg()
{
}

void CEasterEgg::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - EASTER_EGG_BBOX_HEIGHT;
	r = x + EASTER_EGG_BBOX_WIDTH;
	b = y;
}

void CEasterEgg::Render()
{
}

void CEasterEgg::BeTouched(vector<LPGAMEOBJECT>* objects)
{
	CGameObject* nextItem;
	switch (GetNextItemId())
	{
	case ID_ITEM_SMALL_HEART:
		nextItem = new CSmallHeart({ destination.x, destination.y });
		break;
	case ID_ITEM_LARGE_HEART:
		nextItem = new CLargeHeart({ destination.x, destination.y });
		break;
	case ID_ITEM_WHIP_UPGRADE:
		nextItem = new CWhipUpgrade({ destination.x, destination.y });
		break;
	case ID_ITEM_DAGGER:
		nextItem = new CDaggerItem({ destination.x,destination.y });
		break;
	case ID_ITEM_AXE:
		nextItem = new CAxeItem({ destination.x, destination.y });
		break;
	case ID_ITEM_STOPWATCH:
		nextItem = new CStopwatchItem({ destination.x, destination.y });
		break;
	case ID_ITEM_BOOMERANG:
		nextItem = new CBoomerangItem({ destination.x, destination.y });
		break;
	case ID_ITEM_HOLY_WATER:
		nextItem = new CHolyWaterPotion({ destination.x , destination.y });
		break;
	case ID_ITEM_CROSS:
		nextItem = new CCrossItem({ destination.x, destination.y });
		break;
	case ID_ITEM_INVINCIBILITY_POTION:
		nextItem = new CInvincibilityPotion({ destination.x, destination.y });
		break;
	case ID_MONEY_BAG_RED:
	case ID_MONEY_BAG_PURPLE:
	case ID_MONEY_BAG_WHITE:
	case ID_MONEY_BAG_BONUS:
		nextItem = new CMoneyBag({ destination.x, destination.y }, GetNextItemId());
		break;
	default:
		nextItem = NULL;
		break;
	}
	if (nextItem)
		objects->push_back(nextItem);

	state = STATE_DESTROYED;
}
