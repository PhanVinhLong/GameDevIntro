#pragma once
#include "Game.h"
#include "define.h"

#define ID_SCENE_INTRO		0
#define ID_SCENE_PLAY		1
#define ID_SCENE_END		2

class CScene
{
protected:
	int id;
public:
	CScene();
	~CScene();

	virtual void LoadResource() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;

	virtual void OnKeyDown(int keyCode);
	virtual void OnKeyUp(int keyCode);
	virtual void KeyState(BYTE* states);
};

