#include "InvincibilityPotion.h"

CInvincibilityPotion::CInvincibilityPotion(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	id = ID_ITEM_INVINCIBILITY_POTION;
	AddAnimation(ID_ANI_INVINCIBILITY_POTION);
}

CInvincibilityPotion::~CInvincibilityPotion()
{
}

void CInvincibilityPotion::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - INVINCIBILITY_POTION_BBOX_HEIGHT;
	r = x + INVINCIBILITY_POTION_BBOX_WIDTH;
	b = y;
}

void CInvincibilityPotion::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	CItem::Update(dt, objects);

	if (!isOnGround)
		vy += INVINCIBILITY_POTION_GRAVITY * dt;
}
