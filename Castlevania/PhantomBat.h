#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "CrystalBall.h"
#include "HUD.h"

#define PHANTOM_BAT_BBOX_WIDTH			50
#define PHANTOM_BAT_BBOX_HEIGHT			25

#define PHANTOM_BAT_X_START				2600
#define PHANTOM_BAT_X_END				2780

#define PHANTOM_BAT_Y_START				190
#define PHANTOM_BAT_Y_END				280

#define PHANTOM_BAT_STATE_IDLE			0
#define PHANTOM_BAT_STATE_ACTIVE		1
#define PHANTOM_BAT_STATE_ON_FIRE		2

#define PHANTOM_BAT_ANI_IDLE			0
#define PHANTOM_BAT_ANI_ACTIVE			1
#define PHANTOM_BAT_ANI_ON_FIRE			2

#define PHANTOM_BAT_IDLE_TIME			1500
#define PHANTOM_BAT_ATTACK_TIME			1200
#define PHANTOM_BAT_BACK_TIME			1200
#define PHANTOM_BAT_UNTOUCHABLE_TIME	500
#define PHANTOM_BAT_ON_FIRE_TIME		1000

class CPhantomBat :
	public CGameObject
{
	int health;

	DWORD startIdle;
	DWORD startAttack;
	DWORD startBack;
	DWORD startOnFire;
	DWORD startUntouchable;
public:
	CPhantomBat(D3DXVECTOR2 position);
	~CPhantomBat();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render();
	
	virtual void BeDamaged();
};

