#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <fstream>
#include <string>
#include <vector>
#include "json.hpp"
#include "debug.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Viewport.h"
#include "define.h"

#define TILEMAP_CROSS_EFFECT_TIME		1000

// https://github.com/nlohmann/json
using json = nlohmann::json;

class CTileSet
{
private:
	int tileWidth;
	int tileHeight;
	int numOfColumn;
	int numOfRow;

	map<int, RECT> listTile;
	LPDIRECT3DTEXTURE9 texture;
public:
	CTileSet();
	void LoadFromFile(LPCWSTR filePath);
	void DrawTile(int id, D3DXVECTOR2 position, int alpha = 255);
	int GetTileWidth();
	int GetTileHeight();
	~CTileSet();
};

typedef CTileSet* LPTILESET;

class CTileMap
{
private:
	int tileRow;
	int tileColumn;
	int height;
	LPTILESET tileSet;
	int** mapData;

	int wStart;
	int wEnd;

	static DWORD effectStart;
public:
	CTileMap();
	~CTileMap();

	void LoadFromFile(LPCWSTR filePath);
	void Draw(D3DXVECTOR2 position, int alpha = 255);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* object = NULL);

	int GetWidth();
	int GetHeight();

	static void StartEffect() { effectStart = GetTickCount(); }
};

typedef CTileMap* LPTILEMAP;