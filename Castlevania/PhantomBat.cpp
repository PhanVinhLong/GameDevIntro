#include "PhantomBat.h"

CPhantomBat::CPhantomBat(D3DXVECTOR2 position)
{
	this->x = position.x;
	this->y = position.y;

	health = 16;
	id = ID_BOSS_PHANTOM_BAT;

	state = PHANTOM_BAT_STATE_IDLE;

	startIdle = 0;
	startAttack = 0;
	startBack = 0;
	startOnFire = 0;

	AddAnimation(ID_ANI_PHANTOM_BAT_IDLE);
	AddAnimation(ID_ANI_PHANTOM_BAT_ACTIVE);
	AddAnimation(ID_ANI_PHANTOM_BAT_ON_FIRE);
}

CPhantomBat::~CPhantomBat()
{
}

void CPhantomBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (state == PHANTOM_BAT_STATE_ACTIVE)
	{
		left = x;
		top = y - PHANTOM_BAT_BBOX_HEIGHT;
		right = x + PHANTOM_BAT_BBOX_WIDTH;
		bottom = y;
	}
	else
		left = top = right = bottom = 0;
}

void CPhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	x += dx;
	y += dy;

	// check active condition
	if (state == PHANTOM_BAT_STATE_IDLE)
	{
		float sx, sy, px, py;
		CSimon::GetInstance()->GetPosition(sx, sy);
		GetPosition(px, py);
		if (sx - px > 70)
		{
			if (int((sy - HUD_HEIGHT) / 176) == int((py - HUD_HEIGHT) / 176))
			{
				state = PHANTOM_BAT_STATE_ACTIVE;
				startBack = GetTickCount();
				int desX = rand() % 180 + 2600;
				int desY = rand() % 90 + 190 + HUD_HEIGHT;
				vx = (desX - x) / PHANTOM_BAT_BACK_TIME;
				vy = (desY - y) / PHANTOM_BAT_BACK_TIME;
			}
		}
	}

	if (startBack > 0)
	{
		if (GetTickCount() - startBack > PHANTOM_BAT_BACK_TIME)
		{
			startBack = 0;
			startIdle = GetTickCount();
		}
	}
	if (startIdle > 0)
	{
		if (GetTickCount() - startIdle > PHANTOM_BAT_IDLE_TIME)
		{
			startIdle = 0;
			startAttack = GetTickCount();
			float desX, desY;
			CSimon::GetInstance()->GetPosition(desX, desY);
			vx = (desX - x) / PHANTOM_BAT_ATTACK_TIME;
			vy = (desY - y) / PHANTOM_BAT_ATTACK_TIME;
		}
		else
		{
			vx = vy = 0;
		}
	}
	if (startAttack > 0)
	{
		if (GetTickCount() - startAttack > PHANTOM_BAT_ATTACK_TIME)
		{
			startAttack = 0;
			startBack = GetTickCount();
			int desX = rand() % 180 + 2600;
			int desY = rand() % 90 + 190 + HUD_HEIGHT;
			vx = (desX - x) / PHANTOM_BAT_BACK_TIME;
			vy = (desY - y) / PHANTOM_BAT_BACK_TIME;
		}
		else
		{
		}
	}
	// check destroyed
	if (startOnFire > 0 && GetTickCount() - startOnFire > PHANTOM_BAT_ON_FIRE_TIME)
	{
		startOnFire = 0;
		state = STATE_DESTROYED;
	}

	// update untouchable
	if (startUntouchable > 0 && GetTickCount() - startUntouchable > PHANTOM_BAT_UNTOUCHABLE_TIME)
		startUntouchable = 0;
}

void CPhantomBat::Render()
{
	int ani = 0;
	switch (state)
	{
	case PHANTOM_BAT_STATE_IDLE:
		ani = PHANTOM_BAT_ANI_IDLE;
		break;
	case PHANTOM_BAT_STATE_ACTIVE:
		ani = PHANTOM_BAT_ANI_ACTIVE;
		break;
	case PHANTOM_BAT_STATE_ON_FIRE:
		ani = PHANTOM_BAT_ANI_ON_FIRE;
		break;
	default:
		break;
	}
	animations[ani]->Render(x, y);
}

void CPhantomBat::BeDamaged()
{
	if (startUntouchable > 0)
		return;
	startUntouchable = GetTickCount();
	health -= 2;
	if (health < 0)
		health = 0;
	CHUD::GetInstance()->SetEnemyHealth(health);
	if (health == 0 && state == PHANTOM_BAT_STATE_ACTIVE)
	{
		state = PHANTOM_BAT_STATE_ON_FIRE;
		startOnFire = GetTickCount();
		vx = vy = 0;
	}
}
