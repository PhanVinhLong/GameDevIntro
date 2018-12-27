#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "WaterEffect.h"

#define FISHMAN_GRAVITY				0.0006f
#define FISHMAN_SPEED_X				0.02f
#define FISHMAN_JUMP_SPEED_Y		0.35f

#define FISHMAN_ATTACK_TIME			600
#define FISHMAN_ACTIVE_TIME			2000

#define FISHMAN_STATE_ATTACK		9

#define FISHMAN_BBOX_WIDTH			15
#define FISHMAN_BBOX_HEIGHT			28

#define FISHMAN_STATE_JUMP			9

#define FISHMAN_ANI_IDLE_RIGHT		1
#define FISHMAN_ANI_IDLE_LEFT		2
#define FISHMAN_ANI_WALK_RIGHT		3
#define FISHMAN_ANI_WALK_LEFT		4
#define FISHMAN_ANI_ATTACK_RIGHT	5
#define FISHMAN_ANI_ATTACK_LEFT		6


class CFishman :
	public CEnemy
{
	DWORD activeStart;
	DWORD attackStart;

	bool isShowedEffect;
public:
	CFishman(D3DXVECTOR2 position, int nx, int nextItemId);
	~CFishman();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void ColideWithObject(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>* objects);

	void SetState(int state);
};

