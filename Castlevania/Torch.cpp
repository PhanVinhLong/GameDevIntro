#include "Torch.h"

CTorch::CTorch()
{
	x = y = 0;
	AddAnimation(200);
	id = ID_TORCH;
}

CTorch::CTorch(D3DXVECTOR2 position, int nextItemID)
{
	x = position.x;
	y = position.y;
	AddAnimation(200);
	id = ID_TORCH;
	this->nextItemID = nextItemID;
}

CTorch::~CTorch()
{
}

void CTorch::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y - TORCH_BBOX_HEIGHT;
	r = x + TORCH_BBOX_WIDTH;
	b = y;
}

void CTorch::Render()
{
	animations[0]->Render(x, y);
}
