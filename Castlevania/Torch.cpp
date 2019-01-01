#include "Torch.h"

CTorch::CTorch(D3DXVECTOR2 position, int nextItemId)
{
	x = position.x;
	y = position.y;
	AddAnimation(ID_ANI_TORCH);
	id = ID_TORCH;
	this->nextItemId = nextItemId;
}

CTorch::~CTorch()
{
}

void CTorch::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (state == GROUND_OBJ_STATE_NORMAL)
	{
		l = x;
		t = y - TORCH_BBOX_HEIGHT;
		r = x + TORCH_BBOX_WIDTH;
		b = y;
	}
	else
		l = t = r = b = 0;
}

