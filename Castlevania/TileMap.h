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

#define ID_TEX_TILESET_01 -10

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
	void DrawTile(int id, D3DXVECTOR2 position);
	int GetTileWidth();
	int GetTileHeight();
	~CTileSet();
};

typedef CTileSet* LPTILESET;

class CTileMap
{
private:
	int numOfRow;
	int numOfColumn;
	LPTILESET tileSet;
	int** mapData;
public:
	CTileMap();
	void LoadFromFile(LPCWSTR filePath);
	void Draw(D3DXVECTOR2 position);
	~CTileMap();
};
