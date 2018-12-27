#include "Viewport.h"

CViewport::CViewport()
{
	position = { 0, 0 };
	height = 11*16;
	width = 17*16;

	lockUpdate = false;
}

CViewport::CViewport(D3DXVECTOR2 position, int width, int height)
{
	this->position = position;
	this->width = width;
	this->height = height;

	lockUpdate = false;
}

void CViewport::SetPosition(D3DXVECTOR2 position)
{
	this->position = position;
}

void CViewport::MoveRight(DWORD dt)
{
	position.x += VIEWPORT_SPEED_X * dt;
}

D3DXVECTOR2 CViewport::GetPosition()
{
	return position;
}

void CViewport::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = position.x;
	t = position.y + HUD_HEIGHT;
	r = position.x + width;
	b = position.y + height + HUD_HEIGHT;
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
	if (lockUpdate)
		return;

	position.x = playerPos.x - width / 2 + 15;
	// Check if viewport out of world screen
	if (position.x > endPos - width)
		position.x = endPos - width;
	if (position.x < startPos)
		position.x = startPos;
	position.y = int((playerPos.y - HUD_HEIGHT) / 176) * 176;
	if (position.y > 176 * 2)
		position.y = 176 * 2;

}

CViewport* CViewport::__instance = NULL;

CViewport * CViewport::GetInstance()
{
	if (__instance == NULL) __instance = new CViewport();
	return __instance;
}
