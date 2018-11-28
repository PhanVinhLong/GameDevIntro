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

	AddAnimation(111);
	AddAnimation(112);
	AddAnimation(113);
	AddAnimation(114);
	AddAnimation(115);
	AddAnimation(116);
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
	CGameObject::Update(dt, coObjects);
	this->x = playerPos.x;
	this->y = playerPos.y;
	this->nx = playerNx;
	
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
			}
		}
	}
}

void CWhip::Upgrade()
{
	if (level < 2)
		level++;
}
