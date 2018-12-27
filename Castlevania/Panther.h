#pragma once
#include "Enemy.h"
#include "Wall.h"

#define PANTHER_GRAVITY				0.0006f
#define PANTHER_SPEED_X				0.14f
#define PANTHER_JUMP_SPEED_Y		0.15f

#define PANTHER_BBOX_WIDTH			28
#define PANTHER_BBOX_HEIGHT			13

#define PANTHER_STATE_JUMP			9

#define PANTHER_ANI_IDLE_RIGHT		1
#define PANTHER_ANI_IDLE_LEFT		2
#define PANTHER_ANI_RUN_RIGHT		3
#define PANTHER_ANI_RUN_LEFT		4
#define PANTHER_ANI_JUMP_RIGHT		5
#define PANTHER_ANI_JUMP_LEFT		6


class CPanther :
	public CEnemy
{
	CWall* currentFloor;
public:
	CPanther(D3DXVECTOR2 position, int nx, int nextItemId);
	~CPanther();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

