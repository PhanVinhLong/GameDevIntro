#include "Candle.h"

CCandle::CCandle(D3DXVECTOR2 position, int nextItemId)
{
	x = position.x;
	y = position.y;
	AddAnimation(ID_ANI_CANDLE);
	id = ID_CANDLE;
	this->nextItemId = nextItemId;
}

CCandle::~CCandle()
{
}

void CCandle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state == GROUND_OBJ_STATE_NORMAL)
	{
		l = x;
		t = y - CANDLE_BBOX_HEIGHT;
		r = x + CANDLE_BBOX_WIDTH;
		b = y;
	}
	else
		l = t = r = b = 0;
}
