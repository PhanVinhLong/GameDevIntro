#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
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
public:
	~CHUD();

	void Draw(D3DXVECTOR2 position);
	static CHUD* GetInstance();

	LPSPRITE GetItemSprite();
	LPSPRITE GetMultiShootSprite();

	void SetEnemyHealth(int health);
};

typedef CHUD* LPHUD;
