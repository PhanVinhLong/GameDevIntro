#pragma once
#include <algorithm>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Whip.h"
#include "Weapon.h"
#include "Dagger.h"
#include "Axe.h"
#include "HolyWater.h"
#include "Stair.h"
#include "Portal.h"
#include "TileMap.h"
#include "MapSet.h"
#include "WaterEffect.h"
#include "Boomerang.h"
#include "EasterEgg.h"
#include "Scene.h"

#define SIMON_WALKING_SPEED				0.06f
#define SIMON_ON_STAIR_SPEED			0.037f
#define SIMON_JUMP_SPEED_Y				0.21f
#define SIMON_JUMP_DEFLECT_SPEED		0.1f
#define SIMON_GRAVITY					0.0006f
#define SIMON_DIE_DEFLECT_SPEED			0.5f
#define SIMON_MAX_HEALTH				16
#define SIMON_DAMAGED_DEFLECT_SPEED_Y	0.15f
#define SIMON_DAMAGED_DEFLECT_SPEED_X	0.06f

#define SIMON_STATE_IDLE				0
#define SIMON_STATE_WALKING_RIGHT		1
#define SIMON_STATE_WALKING_LEFT		2
#define SIMON_STATE_JUMP				3
#define SIMON_STATE_DIE					4
#define SIMON_STATE_ATTACK				5
#define SIMON_STATE_SIT					6
#define SIMON_STATE_SIT_ATTACK			7
#define SIMON_STATE_ATTACK_SUBWEAPON	8
#define SIMON_STATE_UP_STAIR			9
#define SIMON_STATE_DOWN_STAIR			10
#define SIMON_STATE_ATTACK_ON_STAIR		11
#define SIMON_STATE_DAMAGED_DEFLECT		12
#define SIMON_STATE_FLASH				13

#define SIMON_ANI_IDLE_RIGHT				0
#define SIMON_ANI_IDLE_LEFT					1
#define SIMON_ANI_WALK_RIGHT				2
#define SIMON_ANI_WALK_LEFT					3
#define SIMON_ANI_ATTACK_RIGHT				4
#define SIMON_ANI_ATTACK_LEFT				5
#define SIMON_ANI_SIT_RIGHT					6
#define SIMON_ANI_SIT_LEFT					7
#define SIMON_ANI_SIT_ATTACK_RIGHT			8
#define SIMON_ANI_SIT_ATTACK_LEFT			9
#define SIMON_ANI_DIE						10
#define SIMON_ANI_IDLE_UP_STAIR_RIGHT		11
#define SIMON_ANI_IDLE_UP_STAIR_LEFT		12
#define SIMON_ANI_IDLE_DOWN_STAIR_RIGHT		13
#define SIMON_ANI_IDLE_DOWN_STAIR_LEFT		14
#define SIMON_ANI_WALK_UP_STAIR_RIGHT		15
#define SIMON_ANI_WALK_UP_STAIR_LEFT		16
#define SIMON_ANI_WALK_DOWN_STAIR_RIGHT		17
#define SIMON_ANI_WALK_DOWN_STAIR_LEFT		18
#define SIMON_ANI_ATTACK_UP_STAIR_RIGHT		19
#define SIMON_ANI_ATTACK_UP_STAIR_LEFT		20
#define SIMON_ANI_ATTACK_DOWN_STAIR_RIGHT	21
#define SIMON_ANI_ATTACK_DOWN_STAIR_LEFT	22
#define SIMON_ANI_DAMAGED_DEFLECT_RIGHT		23
#define SIMON_ANI_DAMAGED_DEFLECT_LEFT		24
#define SIMON_ANI_FLASH_RIGHT				25
#define SIMON_ANI_FLASH_LEFT				26

#define SIMON_BBOX_WIDTH			15
#define SIMON_BBOX_HEIGHT			30
#define SIMON_BBOX_SIT_WIDTH		15
#define SIMON_BBOX_SIT_HEIGHT		20

#define SIMON_UNTOUCHABLE_TIME		4000
#define SIMON_ATTACK_TIME			300
#define SIMON_ATTACK_SUB_TIME		300
#define SIMON_JUMP_TIME				650
#define SIMON_INVISIBILITY_TIME		8000
#define SIMON_FLASH_TIME			1000
#define SIMON_LYING_TIME			2000

class CSimon : public CGameObject
{
	CSimon();
	static CSimon* __instance;

	int life;
	int heart;
	int health;
	int time;

	int wMapStart;
	int wMapEnd;

	bool isOnGround;
	bool isJumping;
	bool isFalling;
	bool isOnStair;
	bool lockUpdate;
	bool caculateScore;

	DWORD untouchableStart;
	DWORD attackStart;
	DWORD attackSubStart;
	DWORD jumpStart;
	DWORD invisibilityStart;
	DWORD flashStart;
	DWORD lyingStart;
	DWORD timeStart;
	DWORD calculateStart;

	CWhip* whip;
	CStair* currentStair;
	CStair* colidingStair;
	vector<CWeapon*> subWeapon;
	int subWeaponID;
	int subweaponLevel;

	D3DXVECTOR2 checkPoint;
public:
	~CSimon();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	virtual void RenderBoundingBox(int alpha = 255);

	static CSimon* GetInstance();

	void UpdateOnStairState();
	void UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects);
	void UpdateWhip(DWORD dt, vector<LPGAMEOBJECT>* objects);

	bool IsOnGround() { return isOnGround; }
	bool IsOnStair() { return isOnStair; }

	int GetWidthMapStart() { return wMapStart; }
	int GetWidthMapEnd() { return wMapEnd; }

	int GetHeart() { return heart; }
	int GetHealth() { return health; }
	int GetScore() { return score; }
	int GetSubWeaponID() { return subWeaponID; }
	int GetMultiShootLevel() { return subweaponLevel; }
	int GetTime() { return time; }
	int GetLife() { return life; }
	bool GetLockUpdate() { return lockUpdate; }
	vector<CWeapon*> GetSubWeapon() { return subWeapon; }
	CStair* GetCurrentStair() { return currentStair; }
	CStair* GetColidingStair() { return colidingStair; }

	void ColideWithObject(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>* objects);
	void SetState(int state);
	void SetSubWeapon(int subWeaponID);
	void SetSubWeaponLevel(int level);
	void IncreaseHeart(int heartNum);
	void IncreaseHealth(int num);
	void UpgradeWhip();
	void AddScore(int score);

	void BeDamaged();
	void Respawn();

	void StartAttack();
	void StartAttackSub(vector<LPGAMEOBJECT>* objects);
	void StartJump();
	void StartInvisibility();
	void StartCalculateScore();

	void LockControl() { lockUpdate = true; }
	void UnlockUpdate() { lockUpdate = false; }

	void MoveRight(DWORD dt);

	DWORD GetAttackStart() { return attackStart; }
	DWORD GetJumpStart() { return jumpStart; }

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
