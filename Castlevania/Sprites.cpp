#include "Sprites.h"
#include "Game.h"
#include "debug.h"

CSprite::CSprite(int id, int left, int top, int right, int bottom, int texId, int isFlipHorizonttaly, D3DXVECTOR2 position)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = CTextures::GetInstance()->Get(texId);;
	this->isFlippedHorizontally = isFlipHorizonttaly;
	this->position = position;
}

CSprites * CSprites::__instance = NULL;

CSprites *CSprites::GetInstance()
{
	if (__instance == NULL) __instance = new CSprites();
	return __instance;
}

void CSprite::Draw(float x, float y, int alpha)
{
	CGame * game = CGame::GetInstance();
	float xTmp = x + position.x;
	float yTmp = y + position.y - (bottom - top);
	//game->Draw(x + position.x, y + position.y, texture, left, top, right, bottom, alpha, isFlippedHorizontally);
	game->Draw(xTmp, yTmp, texture, left, top, right, bottom, alpha, isFlippedHorizontally);
}

void CSprites::Add(int id, int left, int top, int right, int bottom, int texId, int isFlippedHorizontally, D3DXVECTOR2 position)
{
	LPSPRITE s = new CSprite(id, left, top, right, bottom, texId, isFlippedHorizontally, position);
	sprites[id] = s;
}

LPSPRITE CSprites::Get(int id)
{
	return sprites[id];
}

void CAnimation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE sprite = CSprites::GetInstance()->Get(spriteId);
	LPANIMATION_FRAME frame = new CAnimationFrame(sprite, t);
	frames.push_back(frame);
}

void CAnimation::Render(float x, float y, int alpha)
{
	CViewport* viewport = CViewport::GetInstance();
	x = viewport->WorldToViewportPos({ x, y }).x;
	y = viewport->WorldToViewportPos({ x, y }).y;

	DWORD now = GetTickCount();

	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size())
				currentFrame = 0;
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void CAnimation::Render(float x, float y, int frame, int alpha)
{
	if (frame == -1 || frame == frames.size())
		frame = 0;
	frames[frame]->GetSprite()->Draw(x, y);
}

void CAnimation::RenderFrame(float x, float y, int alpha)
{
	CViewport* viewport = CViewport::GetInstance();
	x = viewport->WorldToViewportPos({ x, y }).x;
	y = viewport->WorldToViewportPos({ x, y }).y;

	if (currentFrame == -1)
		currentFrame = 0;
	else if (currentFrame == frames.size())
			currentFrame = 0;

	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

CAnimations * CAnimations::__instance = NULL;

CAnimations * CAnimations::GetInstance()
{
	if (__instance == NULL) __instance = new CAnimations();
	return __instance;
}

void CAnimations::Add(int id, LPANIMATION ani)
{
	animations[id] = ani;
}

LPANIMATION CAnimations::Get(int id)
{
	return animations[id];
}
