#include "WhipUpgrade.h"

CWhipUpgrade::CWhipUpgrade(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_WHIP_UPGRADE;
	AddAnimation(301);
}

CWhipUpgrade::~CWhipUpgrade()
{
}

void CWhipUpgrade::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - WHIP_UPGRADE_BBOX_HEIGHT;
	r = x + WHIP_UPGRADE_BBOX_WIDTH;
	b = y;
}

void CWhipUpgrade::Render()
{
	animations[0]->Render(x, y);
}

void CWhipUpgrade::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);
	if(!isOnGround)
		vy += WHIP_UPGRADE_GRAVITY * dt;
}
