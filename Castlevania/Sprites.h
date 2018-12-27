#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>
#include "Viewport.h"
#include "Textures.h"

using namespace std;

class CSprite
{
	int id;				// Sprite ID in the sprite database

	int left;
	int top;
	int right;
	int bottom;

	int isFlippedHorizontally;
	D3DXVECTOR2 position;
	LPDIRECT3DTEXTURE9 texture;
public:
	CSprite(int id, int left, int top, int right, int bottom, int texId, int isFlipHorizontally = 0, D3DXVECTOR2 position = { 0, 0 });

	void Draw(float x, float y, int alpha = 255);
	D3DXVECTOR2 GetPosition() { return this->position; }
};

typedef CSprite * LPSPRITE;

/*
	Manage sprite database
*/
class CSprites
{
	static CSprites * __instance;

	unordered_map<int, LPSPRITE> sprites;

public:
	void Add(int id, int left, int top, int right, int bottom, int texId, int isFlippedHorizontally = 0, D3DXVECTOR2 position = { 0, 0 });
	LPSPRITE Get(int id);

	static CSprites * GetInstance();
};

/*
	Sprite animation
*/
class CAnimationFrame
{
	LPSPRITE sprite;
	DWORD time;
	D3DXVECTOR2 position;
public:
	CAnimationFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; this->position = sprite->GetPosition(); }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }
	D3DXVECTOR2 GetPosition() { return this->position; }
};

typedef CAnimationFrame *LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	vector<LPANIMATION_FRAME> frames;
	bool isFinished;
public:
	CAnimation(int defaultTime, bool isLoop = true) { this->defaultTime = defaultTime; lastFrameTime = -1; currentFrame = -1; isFinished = false; }
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y, int alpha = 255);
	void Render(float x, float y, int frame, int alpha);
	void Reset() { lastFrameTime = -1; currentFrame = -1; }
	int GetCurrentFrame() { return currentFrame; }
	void SetCurrentFrame(int frame) { this->currentFrame = frame; }
	D3DXVECTOR2 GetFramePosition() { return frames[currentFrame]->GetPosition(); }
	bool IsFinished() { return isFinished; }
};

typedef CAnimation *LPANIMATION;

class CAnimations
{
	static CAnimations * __instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Reset() { for (auto iter : animations) iter.second->Reset(); }

	static CAnimations * GetInstance();
};
