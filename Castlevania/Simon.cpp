#include "Simon.h"

CSimon* CSimon::__instance;

CSimon::CSimon()
{
	AddAnimation(ID_ANI_SIMON_IDLE_RIGHT);				// idle right			0
	AddAnimation(ID_ANI_SIMON_IDLE_LEFT);				// idle left			1
	AddAnimation(ID_ANI_SIMON_WALK_RIGHT);				// walk right			2
	AddAnimation(ID_ANI_SIMON_WALK_LEFT);				// walk left			3
	AddAnimation(ID_ANI_SIMON_ATTACK_RIGHT);			// attack right			4
	AddAnimation(ID_ANI_SIMON_ATTACK_LEFT);				// attack left			5
	AddAnimation(ID_ANI_SIMON_SIT_RIGHT);				// sit right			6
	AddAnimation(ID_ANI_SIMON_SIT_LEFT);				// sit left				7
	AddAnimation(ID_ANI_SIMON_SIT_ATTACK_RIGHT);		// sit attack right		8
	AddAnimation(ID_ANI_SIMON_SIT_ATTACK_LEFT);			// sit attack left		9
	AddAnimation(ID_ANI_SIMON_DIE);						// die					10
	AddAnimation(ID_ANI_SIMON_IDLE_UP_STAIR_RIGHT);		// idle up stair r		11
	AddAnimation(ID_ANI_SIMON_IDLE_UP_STAIR_LEFT);		// idle up stair l		12
	AddAnimation(ID_ANI_SIMON_IDLE_DOWN_STAIR_RIGHT);	// idle down stair r	13 
	AddAnimation(ID_ANI_SIMON_IDLE_DOWN_STAIR_LEFT);	// idle down stair l	14
	AddAnimation(ID_ANI_SIMON_WALK_UP_STAIR_RIGHT);		// walk up stair r		15
	AddAnimation(ID_ANI_SIMON_WALK_UP_STAIR_LEFT);		// walk up stair l		16
	AddAnimation(ID_ANI_SIMON_WALK_DOWN_STAIR_RIGHT);	// walk down stair r	17
	AddAnimation(ID_ANI_SIMON_WALK_DOWN_STAIR_LEFT);	// walk down stair l	18
	AddAnimation(ID_ANI_SIMON_ATTACK_UP_STAIR_RIGHT);	// att up stair r		19
	AddAnimation(ID_ANI_SIMON_ATTACK_UP_STAIR_LEFT);	// att up stair l		20
	AddAnimation(ID_ANI_SIMON_ATTACK_DOWN_STAIR_RIGHT);	// att down stair r		21
	AddAnimation(ID_ANI_SIMON_ATTACK_DOWN_STAIR_LEFT);	// att down stair l		22
	AddAnimation(ID_ANI_SIMON_DAMAGED_DEFLECT_RIGHT);	// dmg deflect r		23
	AddAnimation(ID_ANI_SIMON_DAMAGED_DEFLECT_LEFT);	// dmg deflect l		24
	AddAnimation(ID_ANI_SIMON_FLASH_RIGHT);
	AddAnimation(ID_ANI_SIMON_FLASH_LEFT);

	id = ID_SIMON;
	subWeaponID = ID_SUBWEAPON_BOOMERANG;
	subweaponLevel = 1;

	whip = new CWhip();

	life = 3;
	score = 0;
	heart = 5;
	health = 16;

	isOnGround = false;
	isOnStair = false;
	lockUpdate = false;

	currentStair = NULL;
	colidingStair = NULL;

	attackSubStart = 0;
	jumpStart = 0;
	untouchableStart = 0;
	attackStart = 0;
	invisibilityStart = 0;
	flashStart = 0;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	if(!isOnStair)
		vy += SIMON_GRAVITY * dt;

	vector<LPGAMEOBJECT> wallObjects;
		
	for (int i = 0; i < coObjects->size(); i++)
	{
		if(coObjects->at(i)->GetId() == ID_WALL)
			wallObjects.push_back(coObjects->at(i));
	}

	// collision with wall
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision
	if (state != SIMON_STATE_UP_STAIR && state != SIMON_STATE_DOWN_STAIR)
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

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			x += min_tx * dx + nx * 0.1f;		// nx*0.1f : need to push out a bit to avoid overlapping next frame
			y += min_ty * dy + ny * 0.1f;

			if (nx != 0) vx = 0;
			if (ny < 0)
			{
				vy = 0;
				if (!isOnGround) isOnGround = true;
			}
			else y += dy;

			if (attackStart > 0 || attackSubStart > 0)
				vx = 0;
	}

	// clean up collision events
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	colidingStair = NULL;
	// collision with item
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);
	for (auto iter : coEvents)
		ColideWithObject(iter->obj, coObjects);
	for (auto iter : coEvents) delete iter;
	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
	{
		for (auto iter : *coObjects)
		{
			float al, at, ar, ab, bl, bt, br, bb;
			GetBoundingBox(al, at, ar, ab);
			iter->GetBoundingBox(bl, bt, br, bb);
			if (CGame::GetInstance()->IsIntersect({ long(al),long(at),long(ar),long(ab) },
				{ long(bl), long(bt), long(br), long(bb) }))
				ColideWithObject(iter, coObjects);
		}
	}

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchableStart > SIMON_UNTOUCHABLE_TIME && untouchableStart > 0)
		untouchableStart = 0;

	// update attack state and whip
	UpdateWhip(dt, coObjects);

	// update sub weapon
	UpdateSubWeapon(dt, coObjects);

	// update on stair state
	UpdateOnStairState();

	// update invisibility state
	if (GetTickCount() - invisibilityStart > SIMON_INVISIBILITY_TIME && invisibilityStart > 0)
		invisibilityStart = 0;

	// update flash state
	if (GetTickCount() - flashStart > SIMON_FLASH_TIME)
	{
		flashStart = 0;
		UnlockUpdate();
	}
}

void CSimon::Render()
{
	int ani;

	switch (state)
	{
	case SIMON_STATE_DIE:
		ani = SIMON_ANI_DIE;
		break;
	case SIMON_STATE_ATTACK:
		if (nx > 0)
			ani = SIMON_ANI_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_ATTACK_LEFT;
		break;
	case SIMON_STATE_ATTACK_ON_STAIR:
		if (nx > 0 && ny > 0)
			ani = SIMON_ANI_ATTACK_UP_STAIR_RIGHT;
		else if (nx < 0 && ny > 0)
			ani = SIMON_ANI_ATTACK_UP_STAIR_LEFT;
		else if (nx > 0 && ny < 0)
			ani = SIMON_ANI_ATTACK_DOWN_STAIR_RIGHT;
		else if (nx < 0 && ny < 0)
			ani = SIMON_ANI_ATTACK_DOWN_STAIR_LEFT;
		break;
	case SIMON_STATE_SIT_ATTACK:
		if (nx > 0)
			ani = SIMON_ANI_SIT_ATTACK_RIGHT;
		else
			ani = SIMON_ANI_SIT_ATTACK_LEFT;
		break;
	case SIMON_STATE_JUMP:
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
	case SIMON_STATE_SIT:
		if (nx > 0)
			ani = SIMON_ANI_SIT_RIGHT;
		else
			ani = SIMON_ANI_SIT_LEFT;
		break;
	case SIMON_STATE_UP_STAIR:
		if (nx > 0)
			ani = SIMON_ANI_WALK_UP_STAIR_RIGHT;
		else
			ani = SIMON_ANI_WALK_UP_STAIR_LEFT;
		break;
	case SIMON_STATE_DOWN_STAIR:
		if (nx > 0)
			ani = SIMON_ANI_WALK_DOWN_STAIR_RIGHT;
		else
			ani = SIMON_ANI_WALK_DOWN_STAIR_LEFT;
		break;
	case SIMON_STATE_WALKING_RIGHT:
		ani = SIMON_ANI_WALK_RIGHT;
		break;
	case SIMON_STATE_WALKING_LEFT:
		ani = SIMON_ANI_WALK_LEFT;
		break;
	case SIMON_STATE_DAMAGED_DEFLECT:
		if (nx > 0)
			ani = SIMON_ANI_DAMAGED_DEFLECT_RIGHT;
		else
			ani = SIMON_ANI_DAMAGED_DEFLECT_LEFT;
		break;
	case SIMON_STATE_FLASH:
		if (nx > 0)
			ani = SIMON_ANI_FLASH_RIGHT;
		else
			ani = SIMON_ANI_FLASH_LEFT;
		break;
	default:
		if (isOnStair)
		{
			if (nx > 0 && ny > 0)
				ani = SIMON_ANI_IDLE_UP_STAIR_RIGHT;
			else if (nx < 0 && ny > 0)
				ani = SIMON_ANI_IDLE_UP_STAIR_LEFT;
			else if (nx > 0 && ny < 0)
				ani = SIMON_ANI_IDLE_DOWN_STAIR_RIGHT;
			else if (nx < 0 && ny < 0)
				ani = SIMON_ANI_IDLE_DOWN_STAIR_LEFT;
			break;
		}
		else if (nx > 0)
			ani = SIMON_ANI_IDLE_RIGHT;
		else
			ani = SIMON_ANI_IDLE_LEFT;
		break;
	}

	for (auto iter : subWeapon)
		iter->Render();

	int alpha = 255;
	if (invisibilityStart > 0)
		alpha = 90;
	if (untouchableStart > 0)
		alpha = rand() % 100 > 50 ? 80 : 150;
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

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

void CSimon::UpdateOnStairState()
{
	if (isOnStair)
	{
		float sx, sy;
		currentStair->GetPosition(sx, sy);
		if ((currentStair->GetNy() > 0 && (y <= sy - currentStair->GetStairHeight() || y >= sy))
			|| (currentStair->GetNy() < 0 && (y <= sy || y >= sy + currentStair->GetStairHeight())))
		{
			isOnStair = false;
			state = SIMON_STATE_IDLE;
			SetSpeed(0, 0);
		}
	}
}

void CSimon::UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - attackSubStart > SIMON_ATTACK_TIME)
	{
		if (attackSubStart > 0)
		{
			attackSubStart = 0;
			state = state == SIMON_STATE_SIT_ATTACK ? SIMON_STATE_SIT : SIMON_STATE_IDLE;
		}
	}

	for (auto iter : subWeapon)
		iter->Update(dt, objects);
	for (int i = 0; i < subWeapon.size(); i++)
		if (subWeapon[i]->GetState() == STATE_DESTROYED)
		{
			subWeapon.erase(subWeapon.begin() + i);
			i--;
		}
}

void CSimon::UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (GetTickCount() - attackStart <= SIMON_ATTACK_TIME)
	{
		float playerX, playerY;
		playerY = state == SIMON_STATE_SIT_ATTACK ? y + 7 : y;
		playerX = x - 2 * nx;
		whip->Update(dt, objects, { playerX, playerY }, nx);
	}
	else if (attackStart > 0)
	{
		attackStart = 0;
		state = state == SIMON_STATE_SIT_ATTACK ? SIMON_STATE_SIT : SIMON_STATE_IDLE;
	}
}

void CSimon::ColideWithObject(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>* objects)
{
	if (obj->GetState() == STATE_DESTROYED)
		return;

	switch (obj->GetId())
	{
	case ID_ITEM_LARGE_HEART:
		IncreaseHeart(10);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_WHIP_UPGRADE:
		UpgradeWhip();
		obj->SetState(STATE_DESTROYED);
		state = SIMON_STATE_FLASH;
		SetSpeed(0, 0);
		LockUpdate();
		flashStart = GetTickCount();
		break;
	case ID_ITEM_DAGGER:
		SetSubWeapon(ID_SUBWEAPON_DAGGER);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_AXE:
		SetSubWeapon(ID_SUBWEAPON_AXE);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_HOLY_WATER:
		SetSubWeapon(ID_SUBWEAPON_HOLY_WATER);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_BOOMERANG:
		SetSubWeapon(ID_SUBWEAPON_BOOMERANG);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_STOPWATCH:
		SetSubWeapon(ID_SUBWEAPON_STOPWATCH);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_INVINCIBILITY_POTION:
		StartInvisibility();
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_SMALL_HEART:
		IncreaseHeart(1);
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_ITEM_CROSS:
		CTileMap::StartEffect();
		for (auto iter : *objects)
			switch (iter->GetId())
			{
			case ID_PANTHER:
			case ID_GHOUL:
			case ID_BAT:
			case ID_FISHMAN:
			case ID_BULLET:
				iter->SetState(STATE_DESTROYED);
				break;
			default:
				break;
			}
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_PORTAL:
	{
		CPortal* portal = dynamic_cast<CPortal*>(obj);
		SetPosition(portal->GetDestination().x, portal->GetDestination().y);
		break;
	}
	case ID_MAPSET:
	{
		CMapSet* mapSet = dynamic_cast<CMapSet*>(obj);
		wMapStart = mapSet->GetWidthBegin();
		wMapEnd = mapSet->GetWidthEnd();
		break;
	}
	case ID_STAIR:
		if (!isOnStair)
			currentStair = dynamic_cast<CStair*>(obj);
		colidingStair = dynamic_cast<CStair*>(obj);
		break;
	case ID_PANTHER:
	case ID_GHOUL:
	case ID_FISHMAN:
	case ID_BULLET:
	case ID_BOSS_PHANTOM_BAT:
		if (untouchableStart > 0 || invisibilityStart > 0)
			break;
		BeDamaged();
		break;
	case ID_BAT:
		if (untouchableStart > 0 || invisibilityStart > 0)
			break;
		BeDamaged();
		obj->SetState(STATE_DESTROYED);
		break;
	case ID_WATER:
	{
		CWaterEffect* waterEffect = new CWaterEffect({ x, y });
		objects->push_back(waterEffect);
		health = 0;
		state = SIMON_STATE_DIE;
		break;
	}
	case ID_DOOR:
	{
		state = SIMON_STATE_IDLE;
		vx = 0;
		obj->Start();
		break;
	}
	default:
		break;
	}
}

void CSimon::SetState(int state)
{
	if (flashStart > 0)
		return;
	if (attackStart > 0)
		return;
	if (attackSubStart > 0)
		return;
	if (!isOnGround && state != SIMON_STATE_ATTACK && state != SIMON_STATE_ATTACK_SUBWEAPON)
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
		y -= 5;
		break;
	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_UP_STAIR:
		nx = currentStair->GetNx();
		ny = 1;
		SetSpeed(nx*SIMON_ON_STAIR_SPEED, -SIMON_ON_STAIR_SPEED);
		isOnStair = true;
		break;
	case SIMON_STATE_DOWN_STAIR:
		nx = -currentStair->GetNx();
		ny = -1;
		SetSpeed(nx*SIMON_ON_STAIR_SPEED, SIMON_ON_STAIR_SPEED);
		isOnStair = true;
		break;
	case SIMON_STATE_ATTACK:
		break;
	case SIMON_STATE_ATTACK_ON_STAIR:
	case SIMON_STATE_SIT:
		SetSpeed(0, 0);
		break;
	case SIMON_STATE_DAMAGED_DEFLECT:
		break;
	}
}

void CSimon::StartAttack()
{
	if (attackStart > 0)
		return;
	if (attackSubStart > 0)
		return;

	if (state != SIMON_STATE_JUMP)
		vx = 0;

	ResetAnimation();
	whip->ResetAnimation();
	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else if (isOnStair)
		SetState(SIMON_STATE_ATTACK_ON_STAIR);
	else
		SetState(SIMON_STATE_ATTACK);
	attackStart = GetTickCount();
}

void CSimon::StartAttackSub()
{
	if (GetSubWeapon().size() >= subweaponLevel)
		return;

	if (subWeaponID == ID_SUBWEAPON_NONE || heart <= 0)
		return;

	if (attackStart > 0)
		return;
	if (attackSubStart > 0)
		return;

	if (state != SIMON_STATE_JUMP)
		vx = 0;

	ResetAnimation();
	whip->ResetAnimation();
	if (state == SIMON_STATE_SIT)
		SetState(SIMON_STATE_SIT_ATTACK);
	else if (isOnStair)
		SetState(SIMON_STATE_ATTACK_ON_STAIR);
	else
		SetState(SIMON_STATE_ATTACK);
	attackSubStart = GetTickCount();

	switch (subWeaponID)
	{
	case ID_SUBWEAPON_DAGGER:
		subWeapon.push_back(new CDagger({ x, y }, nx));
		break;
	case ID_SUBWEAPON_AXE:
		subWeapon.push_back(new CAxe({ x, y }, nx));
		break;
	case ID_SUBWEAPON_HOLY_WATER:
		subWeapon.push_back(new CHolyWater({ x, y }, nx));
		break;
	case ID_SUBWEAPON_BOOMERANG:
		subWeapon.push_back(new CBoomerang({ x, y }, nx));
		break;
	default:
		break;
	}
	heart--;
}

void CSimon::StartJump()
{
	SetState(SIMON_STATE_JUMP);
	isOnGround = false;
}

void CSimon::StartInvisibility()
{
	invisibilityStart = GetTickCount();
}

void CSimon::MoveRight(DWORD dt)
{
	state = SIMON_STATE_WALKING_RIGHT;
	x += SIMON_WALKING_SPEED * dt;
}

void CSimon::IncreaseHeart(int heartNum)
{
	heart += heartNum;
	DebugOut(L"Heart Increased: %d\n", heart);
}

void CSimon::UpgradeWhip()
{
	whip->Upgrade();
	DebugOut(L"Whip Upgraded\n");
}

void CSimon::AddScore(int score)
{
	this->score += score;
}

void CSimon::BeDamaged()
{
	health -= 2;
	if (health < 0) health = 0;
	untouchableStart = GetTickCount();

	if (!isOnStair)
	{
		SetSpeed(-nx * SIMON_DAMAGED_DEFLECT_SPEED_X, -SIMON_DAMAGED_DEFLECT_SPEED_Y);
		isOnGround = false;
		state = SIMON_STATE_DAMAGED_DEFLECT;
	}
}

void CSimon::SetSubWeapon(int subWeaponID)
{
	this->subWeaponID = subWeaponID;
	DebugOut(L"Weapon Set: %d\n", subWeaponID);
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
	if (state == SIMON_STATE_SIT || state == SIMON_STATE_SIT_ATTACK)
	{
		top = y - SIMON_BBOX_SIT_HEIGHT;
	}
}

