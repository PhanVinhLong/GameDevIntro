#include "Grid.h"

CGrid::CGrid(int column, int row)
{
	this->column = column;
	this->row = row;
	groundObjects = new set<LPGAMEOBJECT>*[row];
	for (int i = 0; i < row; i++)
		groundObjects[i] = new set<LPGAMEOBJECT>[column];
}

CGrid::~CGrid()
{
	// delete groundObjects
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			for (auto iter : groundObjects[i][j])
				delete iter;
			groundObjects[i][j].clear();
		}
		delete[] groundObjects[i];
	}

	// delete moveObjects
	for (auto iter : moveObjects)
		delete iter;
	moveObjects.clear();
}

void CGrid::InsertObject(LPGAMEOBJECT object)
{
	float ol, ot, or , ob, gl, gt, gr, gb;

	object->GetBoundingBox(ol, ot, or , ob);

	for(int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			gl = j * GRID_WIDTH;
			gr = (j + 1) * GRID_WIDTH;
			gt = i * GRID_HEIGHT + HUD_HEIGHT;
			gb = (i + 1) * GRID_HEIGHT + HUD_HEIGHT;
			if (CGame::IsIntersect({ (long)ol, (long)ot, (long)or , (long)ob },
				{ (long)gl, (long)gt, (long)gr, (long)gb }))
				groundObjects[i][j].insert(object);
		}
}

void CGrid::LoadObjects(vector<LPGAMEOBJECT>* objects)
{
	for (auto iter : *objects)
		InsertObject(iter);
}

void CGrid::GetObjects(vector<LPGAMEOBJECT>* objects)
{
	float vl, vt, vr, vb;
	CViewport::GetInstance()->GetBoundingBox(vl, vt, vr, vb);
	int wMin = vl / GRID_WIDTH - 1;
	int wMax = vr / GRID_WIDTH + 1;
	int hMin = vt / GRID_HEIGHT;
	int hMax = vb / GRID_HEIGHT;

	wMin = wMin < 0 ? 0 : wMin;
	wMax = wMax > column ? column : wMax;
	hMin = hMin < 0 ? 0 : hMin;
	hMax = hMax > row ? row : hMax;

	// Add to set to avoid duplication
	set<LPGAMEOBJECT> tmpObjects;
	for (int i = hMin; i < hMax; i++)
		for (int j = wMin; j < wMax; j++)
			for (auto iter : groundObjects[i][j])
				if (iter->GetState() != STATE_DESTROYED)
					tmpObjects.insert(iter);

	for (auto iter : tmpObjects)
		objects->push_back(iter);
}

void CGrid::Update(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	// Store move objects
	moveObjects.clear();
	for(auto iter: *objects)
		switch (iter->GetId())
		{
		case ID_WALL:
		case ID_PORTAL:
		case ID_TORCH:
		case ID_CANDLE:
		case ID_STAIR:
		case ID_MAPSET:
		case ID_ENEMY_SPAWNER:
		case ID_WATER:
		case ID_DOOR:
		case ID_PANTHER:
		case ID_BRICK:
			break;
		default:
			moveObjects.insert(iter);
			break;
		}

	objects->clear();

	// Add ground objects
	GetObjects(objects);

	// Add move objects
	for (auto iter : moveObjects)
		objects->push_back(iter);
}

