#pragma once
#include "debug.h"
#include "Game.h"
#include "Textures.h"
#include "Text.h"
#include "Simon.h"
#include "Sprites.h"
#include "define.h"

class CHUD
{
	static CHUD* __instance;

	LPDIRECT3DTEXTURE9 texBackground;
	LPDIRECT3DTEXTURE9 texHealth;
	unordered_map<int, RECT> listHealth;
	
	LPTEXT text;

	CSimon* player;
	int enemyHealth;

	CHUD();
	void DrawHealth(int id, D3DXVECTOR2 position);

	LPSPRITE GetItemSprite();
	LPSPRITE GetMultiShootSprite();

public:
	~CHUD();

	void Draw(D3DXVECTOR2 position);
	static CHUD* GetInstance();

	void SetEnemyHealth(int health);
};

typedef CHUD* LPHUD;
