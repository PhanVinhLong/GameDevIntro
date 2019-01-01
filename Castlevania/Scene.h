#pragma once
#include "Game.h"
#include "define.h"

class CScene
{
public:
	CScene();
	~CScene();

	virtual void LoadResource() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual void OnKeyDown(int keyCode);
	virtual void OnkeyUp(int keyCode);
	virtual void KeyState(BYTE* states);
};

