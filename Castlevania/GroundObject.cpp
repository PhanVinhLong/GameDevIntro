#include "GroundObject.h"

CGroundObject::CGroundObject()
{
	onFireStart = 0;
	state = GROUND_OBJ_STATE_NORMAL;
	AddAnimation(ID_ANI_ENEMY_ON_FIRE);
}

CGroundObject::~CGroundObject()
{
}

void CGroundObject::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);
	if (GetTickCount() - onFireStart > GROUND_OBJ_ON_FIRE_TIME && onFireStart > 0)
	{
		onFireStart = 0;
		state = STATE_DESTROYED;

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
		default:
			nextItem = NULL;
			break;
		}
		if (nextItem)
			objects->push_back(nextItem);
	}
}

void CGroundObject::Render()
{
	if (state == GROUND_OBJ_STATE_ON_FIRE)
		animations[0]->Render(x, y);
	else
		animations[1]->Render(x, y);
}

void CGroundObject::BeDamaged()
{
	onFireStart = GetTickCount();
	state = GROUND_OBJ_STATE_ON_FIRE;
}
