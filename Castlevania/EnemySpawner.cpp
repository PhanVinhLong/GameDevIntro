#include "EnemySpawner.h"

void CEnemySpawner::SpawnEnemy(vector<LPGAMEOBJECT>* objects)
{
	int playerNx = CSimon::GetInstance()->GetNx();
	float vl, vt, vr, vb;
	CViewport::GetInstance()->GetBoundingBox(vl, vt, vr, vb);

	switch (enemyId)
	{
	case ID_GHOUL:
	{
		float posX = playerNx > 0 ? vr -15 : vl + 5;
		CGhoul* ghoul = new CGhoul({ posX, spawnHeight }, -playerNx, 20);
		objects->push_back(ghoul);
		break;
	}
	case ID_BAT:
	{
		float posX = playerNx > 0 ? vr - 15 : vl + 5;
		CBat* bat = new CBat({ posX, spawnHeight - 40 }, -playerNx, 20);
		objects->push_back(bat);
		break;
	}
	case ID_FISHMAN:
	{
		int enemyNx = GetTickCount() % 2 - 1 > 0 ? 1 : -1;
		float playerX, playerY;
		CSimon::GetInstance()->GetPosition(playerX, playerY);
		float posX = playerX - enemyNx * 80;
		CFishman* fishman = new CFishman({ posX, spawnHeight }, enemyNx, 20);
		objects->push_back(fishman);
		break;
	}
	default:
		break;
	}
}

CEnemySpawner::CEnemySpawner(D3DXVECTOR2 position, int width, int height, int spawnHeight, int enemyId, int numOfEnemy, DWORD delayTime)
{
	this->x = position.x;
	this->y = position.y;
	this->width = width;
	this->height = height;
	this->spawnHeight = spawnHeight + HUD_HEIGHT;
	this->enemyId = enemyId;
	this->num = numOfEnemy;
	this->delayTime = delayTime;

	this->delayStart = 0;
	this->currentIter = 0;
	this->firstSpawn = true;

	id = ID_ENEMY_SPAWNER;
}

CEnemySpawner::~CEnemySpawner()
{
}

void CEnemySpawner::Render()
{
}

void CEnemySpawner::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y - height;
	right = x + width;
	bottom = y;
}

void CEnemySpawner::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	isActive = false;

	float sl, st, sr, sb, l, t, r, b;
	CSimon::GetInstance()->GetBoundingBox(sl, st, sr, sb);
	GetBoundingBox(l, t, r, b);

	if (CGame::GetInstance()->IsIntersect({ long(sl),long(st),long(sr),long(sb) },
		{ long(l), long(t), long(r), long(b) }))
	{
		isActive = true;
		if (firstSpawn)
		{
			delayStart = GetTickCount() - delayTime - currentIter * SPAWNER_DELAY_TIME - 1;
			firstSpawn = false;
		}
		else if (delayStart == 0)
			delayStart = GetTickCount();
	}

	if (GetTickCount() - delayStart > delayTime + currentIter* SPAWNER_DELAY_TIME && delayStart > 0)
	{
		if(!isActive)
			delayStart = GetTickCount() - delayTime - currentIter * SPAWNER_DELAY_TIME;
		else
		{
			currentIter++;
			if (currentIter == num)
			{
				currentIter = 0;
				delayStart = 0;
			}

			int tmp = 0;
			for (auto iter : *objects)
				if (iter->GetId() == enemyId)
					tmp++;

			if (tmp < num)
				SpawnEnemy(objects);
		}
	}
}
