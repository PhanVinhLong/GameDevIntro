#pragma once
#include "GameObject.h"
#include "Simon.h"
#include "Viewport.h"

#define ENEMY_ON_FIRE_TIME			450

#define ENEMY_STATE_ON_FIRE			0
#define ENEMY_STATE_IDLE			1
#define ENEMY_STATE_ACTIVE			2

#define ENEMY_ANI_ON_FIRE			0

class CEnemy :
	public CGameObject
{
protected:
	DWORD onFireStart;
public:
	CEnemy();
	~CEnemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objetcs);

	int GetScore() { return score; }

	void BeDamaged();
};

