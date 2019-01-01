#include "Door.h"

CDoor::CDoor(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;

	id = ID_DOOR;

	state = DOOR_STATE_CLOSE;

	action1Start = 0;
	action2Start = 0;
	action3Start = 0;
	action4Start = 0;
	action5Start = 0;

	AddAnimation(ID_ANI_DOOR_OPEN);
	AddAnimation(ID_ANI_DOOR_CLOSE);
	AddAnimation(ID_ANI_DOOR_OPENING);
	AddAnimation(ID_ANI_DOOR_CLOSING);
}

CDoor::~CDoor()
{
}

void CDoor::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state == DOOR_STATE_CLOSE)
	{
		l = x;
		t = y - DOOR_BBOX_HEIGHT;
		r = x + DOOR_BBOX_WIDTH;
		b = y;
	}
	else
		l = t = r = b = 0;
}

void CDoor::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	if (action1Start > 0)
	{
		if (GetTickCount() - action1Start > DOOR_ACTION_1_TIME)
		{
			action1Start = 0;
			action2Start = GetTickCount();
		}
		else
		{
			simon->LockControl();
			viewport->LockUpdate();
			viewport->MoveRight(dt);
		}
	}
	if (action2Start > 0)
	{
		if (GetTickCount() - action2Start > DOOR_ACTION_2_TIME)
		{
			action2Start = 0;
			action3Start = GetTickCount();
		}
		else
		{
			state = DOOR_STATE_OPENING;
		}
	}
	if (action3Start > 0)
	{
		if (GetTickCount() - action3Start > DOOR_ACTION_3_TIME)
		{
			action3Start = 0;
			action4Start = GetTickCount();
		}
		else
		{
			state = DOOR_STATE_OPEN;
			simon->MoveRight(dt);
		}
	}
	if (action4Start > 0)
	{
		if (GetTickCount() - action4Start > DOOR_ACTION_4_TIME)
		{
			action4Start = 0;
			action5Start = GetTickCount();
		}
		else
		{
			simon->SetState(SIMON_STATE_IDLE);
			state = DOOR_STATE_CLOSING;
		}
	}
	if (action5Start > 0)
	{
		if (GetTickCount() - action5Start > DOOR_ACTION_5_TIME)
		{
			action5Start = 0;
			simon->UnlockUpdate();
			viewport->UnlockUpdate();
			id = ID_WALL;
		}
		else
		{
			state = DOOR_STATE_CLOSE;
			viewport->MoveRight(dt);
		}
	}
}

void CDoor::Render()
{
	int ani = 0;
	switch (state)
	{
	case DOOR_STATE_OPEN:
		ani = DOOR_ANI_OPEN;
		break;
	case DOOR_STATE_CLOSE:
		ani = DOOR_ANI_CLOSE;
		break;
	case DOOR_STATE_OPENING:
		ani = DOOR_ANI_OPENING;
		break;
	case DOOR_STATE_CLOSING:
		ani = DOOR_ANI_CLOSING;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void CDoor::Start()
{
	if (action1Start > 0 || action2Start > 0 || action3Start > 0 || action4Start > 0 || action5Start > 0)
		return;
	action1Start = GetTickCount();
}
