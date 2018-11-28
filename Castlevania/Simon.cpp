#include "Simon.h"

CSimon::CSimon()
{
	untouchableStart = 0;
	attackStart = 0;
	isOnGround = false;
	id = ID_SIMON;
	whip = new CWhip();
	heart = 5; subWeaponID = -1;
	attackStartSub = 0;
	jumpStart = 0;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;

	// collision with wall
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	vector<LPGAMEOBJECT> wallObjects;
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetID() == ID_WALL)
			wallObjects.push_back(coObjects->at(i));

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(&wallObjects, coEvents);

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		int idx, idy;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, idx, idy);

		x += min_tx * dx + nx * 0.1f;		// nx*0.1f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.1f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	// clean up collision events
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// collision with item

	vector<LPGAMEOBJECT> itemObjects;
	for (int i = 0; i < coObjects->size(); i++)
		if (coObjects->at(i)->GetID() == ID_LARGE_HEART
			|| coObjects->at(i)->GetID() == ID_WHIP_UPGRADE
			|| coObjects->at(i)->GetID() == ID_DAGGER_ITEM)
			itemObjects.push_back(coObjects->at(i));

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
	{
		for (auto iter : itemObjects)
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (CGame::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
			{
				float a, b;
				iter->GetPosition(a, b);
				CGameObject* nextItem;
				switch (iter->GetID())
				{
				case ID_LARGE_HEART:
					IncreaseHeart(10);
					break;
				case ID_WHIP_UPGRADE:
					UpgradeWhip();
					break;
				case ID_DAGGER_ITEM:
					SetSubWeapon(ID_DAGGER);
					break;
				default:
					break;
				}
				iter->SetState(STATE_DESTROYED);
			}
		}
	}

	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// update attack state and whip
	if (GetTickCount() - attackStart <= SIMON_ATTACK_TIME)
	{
		whip->Update(dt, coObjects, { x, y }, nx);
	}
	else if (attackStart > 0)
	{
		attackStart = 0;
		state = SIMON_STATE_IDLE;
	}

	// update sub weapon
	if (GetTickCount() - attackStartSub > SIMON_ATTACK_TIME)
	{
		attackStartSub = 0;
		state = SIMON_STATE_IDLE;
	}

	for (auto iter : subWeapon)
		iter->Update(dt, coObjects);
	for (int i = 0; i < subWeapon.size(); i++)
		if (subWeapon[i]->GetState() == STATE_DESTROYED)
		{
			subWeapon.erase(subWeapon.begin() + i);
			i--;
		}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME)
	{
		untouchableStart = 0;
		untouchable = 0;
	}

	// update jump state
	if (GetTickCount() - jumpStart > SIMON_JUMP_TIME)
		jumpStart = 0;

}

void CSimon::Render()
{
	int ani;
	if (state == SIMON_STATE_DIE)
		ani = SIMON_ANI_DIE;
	else if (state == SIMON_STATE_ATTACK)
	{
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
	}
	else if (state == SIMON_STATE_ATTACK_SUBWEAPON)
	{
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
	}
	else if (state == SIMON_STATE_JUMP)
	{
		if (vy < 0)
		{
			if (nx > 0)
				ani = SIMON_ANI_SIT_RIGHT;
			else
				ani = SIMON_ANI_SIT_LEFT;
		}
		else
			if (nx > 0)
				ani = SIMON_ANI_IDLE_RIGHT;
			else
				ani = SIMON_ANI_IDLE_LEFT;
	}
	else if (state == SIMON_STATE_SIT)
	{
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;
	}
	else
	{
		if (vx == 0)
		{
			if (nx > 0)
				ani = SIMON_ANI_IDLE_RIGHT;
			else
				ani = SIMON_ANI_IDLE_LEFT;
		}
		else
			if (vx > 0)
				ani = SIMON_ANI_WALKING_RIGHT;
			else
				ani = SIMON_ANI_WALKING_LEFT;
	}

	for (auto iter : subWeapon)
		iter->Render();

	int alpha = 255;
	if (untouchableStart > 0)
		alpha = 128;
	animations[ani]->Render(x, y, alpha);

	if (attackStart)
		whip->Render();
}

void CSimon::RenderBoundingBox(int alpha)
{
	CGameObject::RenderBoundingBox(alpha);
	whip->RenderBoundingBox(alpha);
	for (auto iter : subWeapon)
		iter->RenderBoundingBox(alpha);
}

//void CSimon::CalcPotentialCollisions(
//	vector<LPGAMEOBJECT> *coObjects,
//	vector<LPCOLLISIONEVENT> &coEvents)
//{
//	for (UINT i = 0; i < coObjects->size(); i++)
//	{
//		if (coObjects->at(i)->GetID() != ID_TORCH)
//		{
//			LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));
//
//			if (e->t > 0 && e->t <= 1.0f)
//				coEvents.push_back(e);
//			else
//				delete e;
//		}
//	}
//
//	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
//}

void CSimon::SetState(int state)
{
	if (attackStart > 0)
		return;
	if (attackStartSub > 0)
		return;
	if (jumpStart > 0 && state != SIMON_STATE_ATTACK && state != SIMON_STATE_ATTACK_SUBWEAPON)
		return;

	int preState = state;
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_ATTACK:
		break;
	}
}

void CSimon::StartUntouchable()
{
	untouchable = 1;
	untouchableStart = GetTickCount();
}

void CSimon::StartAttack()
{
	if (attackStart > 0)
		return;
	if (attackStartSub > 0)
		return;

	if (state != SIMON_STATE_JUMP)
		vx = 0;

	ResetAnimation();
	whip->ResetAnimation();
	SetState(SIMON_STATE_ATTACK);
	attackStart = GetTickCount();
}

void CSimon::StartAttackSub()
{
	if (subWeaponID == ID_SUBWEAPON_NONE || heart <= 0)
		return;

	SetState(SIMON_STATE_ATTACK_SUBWEAPON);
	attackStartSub = GetTickCount();
	switch (subWeaponID)
	{
	case ID_DAGGER:
		subWeapon.push_back(new CDagger({ x, y }, nx));
		break;
	default:
		break;
	}
	heart--;
}

void CSimon::StartJump()
{
	SetState(SIMON_STATE_JUMP);
	jumpStart = GetTickCount();
}

void CSimon::IncreaseHeart(int heartNum)
{
	heart += heartNum;
	DebugOut(L"Heart Increased: %d", heart);
}

void CSimon::UpgradeWhip()
{
	whip->Upgrade();
	DebugOut(L"Whip Upgraded");
}

void CSimon::SetSubWeapon(int subWeaponID)
{
	this->subWeaponID = subWeaponID;
	DebugOut(L"Weapon Seted: %d", subWeaponID);
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	/*left = x;
	top = y;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y + SIMON_BBOX_HEIGHT;*/
	left = x;
	top = y - SIMON_BBOX_HEIGHT;
	right = x + SIMON_BBOX_WIDTH;
	bottom = y;
}

