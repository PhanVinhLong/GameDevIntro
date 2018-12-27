#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "debug.h"
#include "define.h"

#define VIEWPORT_SPEED_X	 0.065f

class CViewport
{
private:
	static CViewport* __instance;
	D3DXVECTOR2 position;
	int width;
	int height;

	bool lockUpdate;
public:
	CViewport();
	CViewport(D3DXVECTOR2 position, int width, int height);
	~CViewport() {}

	D3DXVECTOR2 WorldToViewportPos(D3DXVECTOR2 worldPos);
	D3DXVECTOR2 ViewportToWorldPos(D3DXVECTOR2 viewportPos);

	void Update(D3DXVECTOR2 playerPos,	int startPos, int endPos);

	static CViewport* GetInstance();

	D3DXVECTOR2 GetPosition();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void SetPosition(D3DXVECTOR2 position);
	
	void MoveRight(DWORD dt);

	void LockUpdate() { lockUpdate = true; }
	void UnlockUpdate() { lockUpdate = false; }
};

typedef CViewport* LPVIEWPORT;
