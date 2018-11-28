#pragma once
#include "GameObject.h"
#include "Textures.h"
#include "Game.h"
#include "LargeHeart.h"
#include "WhipUpgrade.h"
#include "DaggerItem.h"

#define ID_TEX_WHIP			30

#define WHIP_BBOX_WIDTH_01		25
#define WHIP_BBOX_HEIGHT_01		8
#define WHIP_BBOX_WIDTH_02		25
#define WHIP_BBOX_HEIGHT_02		8
#define WHIP_BBOX_WIDTH_03		40
#define WHIP_BBOX_HEIGHT_03		8

#define WHIP_ANI_RIGHT_01	0
#define WHIP_ANI_LEFT_01	1
#define WHIP_ANI_RIGHT_02	2
#define WHIP_ANI_LEFT_02	3
#define WHIP_ANI_RIGHT_03	4
#define WHIP_ANI_LEFT_03	5

class CSimon;

class CWhip :
	public CGameObject
{
private:
	int level;
	int GetCurrentAnimation();
public:
	CWhip();
	~CWhip();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	void Render(int frame);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects, D3DXVECTOR2 playerPos, int playerNx);
	void Upgrade();
};

typedef CWhip* LPWHIP;
