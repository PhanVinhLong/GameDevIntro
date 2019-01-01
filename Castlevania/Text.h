#pragma once
#include "debug.h"
#include "Game.h"
#include "Textures.h"

#define ID_TEX_FONT	-20

class CText
{
	static CText* __instance;

	unordered_map<int, RECT> listChar;
	LPDIRECT3DTEXTURE9 texture;
	int charWidth;
	int charHeight;
	int column;
	int numOfChar;

	CText();
	
	void DrawChar(char c, D3DXVECTOR2 position);
public:
	~CText();

	static CText* GetInstance();

	void DrawString(char* s, D3DXVECTOR2 position);
};

typedef CText* LPTEXT;
