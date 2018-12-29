#include "Weapon.h"

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;
	
	for (auto iter : *objects)
	{
		// normal intersect colision
		switch (iter->GetId())
		{
		case ID_TORCH:
		case ID_CANDLE:
		case ID_PANTHER:
		case ID_BAT:
		case ID_GHOUL:
		case ID_FISHMAN:
		case ID_BULLET:
		case ID_BOSS_PHANTOM_BAT:
		case ID_BRICK:
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (CGame::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				iter->BeDamaged();
				if (id == ID_SUBWEAPON_DAGGER)
					state = STATE_DESTROYED;
			}
			break;
		}
		default:
			break;
		}
	}

	// sweptAABB colision
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	if (state != STATE_DESTROYED)
		CalcPotentialCollisions(objects, coEvents);
	for (auto iter : coEvents)
	{
		switch (iter->obj->GetId())
		{
		case ID_TORCH:
		case ID_CANDLE:
		case ID_PANTHER:
		case ID_BAT:
		case ID_GHOUL:
		case ID_FISHMAN:
		case ID_BOSS_PHANTOM_BAT:
		case ID_BRICK:
			iter->obj->BeDamaged();
			if (id == ID_SUBWEAPON_DAGGER)
				state = STATE_DESTROYED;
			break;
		default:
			break;
		}
	}
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// delete when out of screen
	float vl, vt, vr, vb, l, t, r, b;
	CViewport::GetInstance()->GetBoundingBox(vl, vt, vr, vb);
	GetBoundingBox(l, t, r, b);
	if (!(CGame::IsIntersect({ (long)vl, (long)vt, (long)vr, (long)vb },
		{ (long)l, (long)t, (long)r, (long)b })))
		state = STATE_DESTROYED;
}
