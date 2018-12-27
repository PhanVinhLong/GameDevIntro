#pragma once
#include <ctime>
#include "GameObject.h"
#include "Viewport.h"
#include "Simon.h"
#include "Ghoul.h"
#include "Bat.h"
#include "Fishman.h"

#define SPAWNER_DELAY_TIME		800

class CEnemySpawner :
	public CGameObject
{
	int width;
	int height;
	float spawnHeight;
	int enemyId;
	int num;
	int delayTime;
	
	int currentIter;
	bool isActive;
	DWORD delayStart;

	bool firstSpawn;

	void SpawnEnemy(vector<LPGAMEOBJECT>* objects);
public:
	CEnemySpawner(D3DXVECTOR2 position, int width, int height, int spawnHeight, int enemyId, int numOfEnemy, DWORD delayTime);
	~CEnemySpawner();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};

