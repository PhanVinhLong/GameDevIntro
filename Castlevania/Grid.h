#pragma once
#include <set> 
#include "Game.h"
#include "GameObject.h"
#include "Viewport.h"

class CGrid
{
	set<LPGAMEOBJECT>** groundObjects;
	set<LPGAMEOBJECT> moveObjects;
	int column;
	int row;
public:
	CGrid(int column, int row);
	~CGrid();

	void InsertObject(LPGAMEOBJECT object);
	void LoadObjects(vector<LPGAMEOBJECT>* objects);
	void GetObjects(vector<LPGAMEOBJECT>* objects);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

typedef CGrid* LPGRID;