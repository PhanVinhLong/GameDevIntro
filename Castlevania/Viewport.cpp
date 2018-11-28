#include "Viewport.h"

CViewport::CViewport()
{
	position = { 0, 0 };
	height = 176;
	width = 256;
}

CViewport::CViewport(D3DXVECTOR2 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;
}

void CViewport::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

D3DXVECTOR2 CViewport::GetPosition()
{
	return position;
}

D3DXVECTOR2 CViewport::WorldToViewportPos(D3DXVECTOR2 worldPos)
{
	return { worldPos.x - position.x, worldPos.y - position.y };
}

D3DXVECTOR2 CViewport::ViewportToWorldPos(D3DXVECTOR2 viewportPos)
{
	return { viewportPos.x + position.x, viewportPos.y + position.y };
}

void CViewport::Update(D3DXVECTOR2 playerPos, int startPos, int endPos)
{
	position.x = playerPos.x - width / 2 + 15;
	// Check if viewport out of world screen
	if (position.x < startPos)
		position.x = startPos;
	if (position.x > endPos - width)
		position.x = endPos - width;
	position.y = int((playerPos.y - 50) / 176) * 176;
	if (position.y > 176 * 3 - height)
		position.y = 176 * 3 - height;
}

CViewport* CViewport::__instance = NULL;

CViewport * CViewport::GetInstance()
{
	if (__instance == NULL) __instance = new CViewport();
	return __instance;
}
