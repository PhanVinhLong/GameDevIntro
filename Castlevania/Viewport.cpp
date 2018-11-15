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

void CViewport::Update(D3DXVECTOR2 playerPos)
{
	position.x = playerPos.x - width / 2 + 15;
	// Check if viewport out of world screen
	if (position.x < 0)
		position.x = 0;
	if (position.y < 0)
		position.y = 0;
}

CViewport* CViewport::__instance = NULL;

CViewport * CViewport::GetInstance()
{
	if (__instance == NULL) __instance = new CViewport();
	return __instance;
}
