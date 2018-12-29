#include "CrystalBall.h"

CCrystalBall::CCrystalBall(D3DXVECTOR2 position)
{
	x = position.x;
	y = position.y;
	this->id = ID_CRYSTAL_BALL;
	AddAnimation(ID_ANI_CRYSTAL_BALL);
}

CCrystalBall::~CCrystalBall()
{
}

void CCrystalBall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y -CRYSTAL_BALL_BBOX_HEIGHT;
	r = x +CRYSTAL_BALL_BBOX_WIDTH;
	b = y;
}

void CCrystalBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CItem::Update(dt, coObjects);

	if (!isOnGround)
		vy +=CRYSTAL_BALL_GRAVITY * dt;

	disappearStart = 0;
}
