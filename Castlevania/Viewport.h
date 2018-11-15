#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "debug.h"

class CViewport
{
private:
	static CViewport* __instance;
	D3DXVECTOR2 position;
	int width;
	int height;
public:
	CViewport();
	CViewport(D3DXVECTOR2 position, int width, int height);
	void SetPosition(D3DXVECTOR2 position);
	D3DXVECTOR2 GetPosition();
	D3DXVECTOR2 WorldToViewportPos(D3DXVECTOR2 worldPos);
	D3DXVECTOR2 ViewportToWorldPos(D3DXVECTOR2 viewportPos);
	void Update(D3DXVECTOR2 playerPos);
	static CViewport* GetInstance();
	~CViewport() {}
};
