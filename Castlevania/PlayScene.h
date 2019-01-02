#pragma once
#include "Scene.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

#include "define.h"
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "json.hpp"

#include "Simon.h"
#include "Torch.h"
#include "LargeHeart.h"
#include "Wall.h"
#include "Portal.h"
#include "Stair.h"
#include "EnemySpawner.h"
#include "Water.h"
#include "Door.h"
#include "CheckPoint.h"
#include "Brick.h"

#include "TileMap.h"
#include "Viewport.h"
#include "HUD.h"
#include "Text.h"
#include "Candle.h"
#include "Panther.h"
#include "MapSet.h"
#include "PhantomBat.h"
#include "Grid.h"

class CPlayScene :
	public CScene
{
	LPGAME game;
	LPVIEWPORT viewport;
	LPTILEMAP tileMap;
	LPHUD hud;
	LPGRID grid;

	CSimon* simon;

	vector<LPGAMEOBJECT> objects;

public:
	CPlayScene();
	~CPlayScene();

	void LoadResource();
	void Update(DWORD dt);
	void Render();

	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
	void KeyState(BYTE* states);
};

