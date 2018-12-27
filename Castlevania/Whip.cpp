#include "Whip.h"

int CWhip::GetCurrentAnimation()
{
	int ani = 0;
	if (level == 0 && nx > 0)
		ani = 0;
	else if (level == 0 && nx < 0)
		ani = 1;
	else if (level == 1 && nx > 0)
		ani = 2;
	else if (level == 1 && nx < 0)
		ani = 3;
	else if (level == 2 && nx > 0)
		ani = 4;
	else
		ani = 5;

	return ani;
}

CWhip::CWhip()
{
	level = 0;
	id = ID_WHIP;
	vx = 0;
	vy = 0;

	AddAnimation(ID_ANI_WHIP_0_RIGHT);
	AddAnimation(ID_ANI_WHIP_0_LEFT);
	AddAnimation(ID_ANI_WHIP_1_RIGHT);
	AddAnimation(ID_ANI_WHIP_1_LEFT);
	AddAnimation(ID_ANI_WHIP_2_RIGHT);
	AddAnimation(ID_ANI_WHIP_2_LEFT);
}

CWhip::~CWhip()
{
}

void CWhip::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (animations[GetCurrentAnimation()]->GetCurrentFrame() == 2)
	{
		int w, h;
		switch (level)
		{
		case 0:
			w = WHIP_BBOX_WIDTH_01;
			h = WHIP_BBOX_HEIGHT_01;
			break;
		case 1:
			w = WHIP_BBOX_WIDTH_02;
			h = WHIP_BBOX_HEIGHT_02;
			break;
		case 2:
			w = WHIP_BBOX_WIDTH_03;
			h = WHIP_BBOX_HEIGHT_03;
			break;
		}
		l = x + animations[GetCurrentAnimation()]->GetFramePosition().x;
		t = y + animations[GetCurrentAnimation()]->GetFramePosition().y - h;
		r = l + w;
		b = y + animations[GetCurrentAnimation()]->GetFramePosition().y;
	}
	else
		l = t = r = b = 0.0f;
}

void CWhip::Render()
{
	animations[GetCurrentAnimation()]->Render(x, y);
}

void CWhip::Render(int frame)
{
	animations[GetCurrentAnimation()]->Render(x, y, frame, 255);
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, D3DXVECTOR2 playerPos, int playerNx)
{
	CWeapon::Update(dt, coObjects);

	this->x = playerPos.x;
	this->y = playerPos.y;
	this->nx = playerNx;
}

void CWhip::Upgrade()
{
	if (level < 2)
		level++;
}
