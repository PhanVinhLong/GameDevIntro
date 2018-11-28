#include "Weapon.h"

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->GetID() == ID_TORCH)
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			coObjects->at(i)->GetBoundingBox(bl, bt, br, bb);
			if (CGame::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				float a, b;
				coObjects->at(i)->GetPosition(a, b);
				CGameObject* nextItem;
				switch (coObjects->at(i)->GetNextItemID())
				{
				case ID_LARGE_HEART:
					nextItem = new CLargeHeart({ a, b });
					break;
				case ID_WHIP_UPGRADE:
					nextItem = new CWhipUpgrade({ a, b });
					break;
				case ID_DAGGER_ITEM:
					nextItem = new CDaggerItem({ a, b });
					break;
				default:
					nextItem = NULL;
					break;
				}
				if (nextItem)
					coObjects->push_back(nextItem);
				coObjects->at(i)->SetState(STATE_DESTROYED);
				this->SetState(STATE_DESTROYED);
			}
		}
	}
}
