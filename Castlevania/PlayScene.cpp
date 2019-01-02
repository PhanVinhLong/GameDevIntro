#include "PlayScene.h"

CPlayScene::CPlayScene()
{
	id = ID_SCENE_PLAY;
	SetCurrentSceneId(ID_SCENE_PLAY);
	LoadResource();
}

CPlayScene::~CPlayScene()
{
	delete viewport;
	delete tileMap;
	delete grid;
	delete simon;
	delete hud;
}

void CPlayScene::LoadResource()
{
	game = CGame::GetInstance();

	viewport = CViewport::GetInstance();

	tileMap = new CTileMap();
	tileMap->LoadFromFile(L"textures\\map01.json");

	grid = new CGrid(22, 6);

	ifstream file("textures\\map01.json");
	json j = json::parse(file);

	for (auto i : j["layers"])
	{
		if (i["name"] == "wall")	// wall objects
			for (auto iter : i["objects"])
			{
				CWall* wall = new CWall({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["width"], iter["height"]);
				objects.push_back(wall);
			}
		else if (i["name"] == "water")	// water objects
			for (auto iter : i["objects"])
			{
				CWater* water = new CWater({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["width"], iter["height"]);
				objects.push_back(water);
			}
		else if (i["name"] == "door")	// water objects
		{
			for (auto iter : i["objects"])
			{
				CDoor* door = new CDoor({ float(iter["x"]), float(iter["y"]) + iter["height"] });
				objects.push_back(door);
			}
		}
		else if (i["name"] == "candle")	// candle objects
			for (auto iter : i["objects"])
			{
				CCandle* candle = new CCandle({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["properties"][0]["value"]);
				objects.push_back(candle);
			}
		else if (i["name"] == "torch")	// torch objects
			for (auto iter : i["objects"])
			{
				CTorch* torch = new CTorch({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["properties"][0]["value"]);
				objects.push_back(torch);
			}
		else if (i["name"] == "stair")	// stair objects5
			for (auto iter : i["objects"])
			{
				CStair* stair = new CStair({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["width"], iter["height"], iter["properties"][0]["value"],
					iter["properties"][1]["value"], iter["properties"][2]["value"]);
				objects.push_back(stair);
			}
		else if (i["name"] == "panther")	// panther enemies
			for (auto iter : i["objects"])
			{
				CPanther* panther = new CPanther({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["properties"][0]["value"], iter["properties"][1]["value"]);
				objects.push_back(panther);
			}
		else if (i["name"] == "boss")	// boss
			for (auto iter : i["objects"])
			{
				CPhantomBat* phantomBat = new CPhantomBat({ float(iter["x"]), float(iter["y"]) + iter["height"] });
				objects.push_back(phantomBat);
			}
		else if (i["name"] == "portal")
			for (auto iter : i["objects"])
			{
				CPortal* portal = new CPortal({ float(iter["x"]), float(iter["y"]) + iter["height"] }, { iter["properties"][0]["value"], iter["properties"][1]["value"] });
				objects.push_back(portal);
			}
		else if (i["name"] == "mapset")
			for (auto iter : i["objects"])
			{
				CMapSet* mapset = new CMapSet({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["properties"][0]["value"], iter["properties"][1]["value"]);
				objects.push_back(mapset);
			}
		else if (i["name"] == "enemyspawner")
			for (auto iter : i["objects"])
			{
				CEnemySpawner* spawner = new CEnemySpawner({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["width"], iter["height"],
					iter["properties"][0]["value"], iter["properties"][1]["value"], iter["properties"][2]["value"], iter["properties"][3]["value"]);
				objects.push_back(spawner);
			}
		else if (i["name"] == "checkpoint")
			for (auto iter : i["objects"])
			{
				CCheckPoint* checkPoint = new CCheckPoint({ float(iter["x"]), float(iter["y"]) + iter["height"] });
				objects.push_back(checkPoint);
			}
		else if (i["name"] == "brick")
			for (auto iter : i["objects"])
			{
				CBrick* brick = new CBrick({ float(iter["x"]), float(iter["y"]) + iter["height"] }, iter["properties"][0]["value"]);
				objects.push_back(brick);
			}
		else if (i["name"] == "easteregg")
			for (auto iter : i["objects"])
			{
				CEasterEgg* eg = new CEasterEgg({ float(iter["x"]), float(iter["y"]) + iter["height"] },
					{ iter["properties"][0]["value"], iter["properties"][1]["value"] }, iter["properties"][2]["value"]);
				objects.push_back(eg);
			}
	}

	// add a HUD_HEIGHT to objects's heigth
	for (auto iter : objects)
		iter->AddPosition(0, HUD_HEIGHT);

	grid->LoadObjects(&objects);

	// Add simon
	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 143.0f + HUD_HEIGHT);

	hud = CHUD::GetInstance();
}

void CPlayScene::Update(DWORD dt)
{
	grid->Update(dt, &objects);

	simon->Update(dt, &objects);

	for (auto iter : objects)
		iter->Update(dt, &objects);

	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetState() == STATE_DESTROYED)
		{
			objects.erase(objects.begin() + i);
			i--;
		}
	}

	// Update viewport
	D3DXVECTOR2 playerPos;
	simon->GetPosition(playerPos.x, playerPos.y);
	viewport->Update(playerPos, simon->GetWidthMapStart() * TILE_WIDTH, simon->GetWidthMapEnd() * TILE_WIDTH);
	tileMap->Update(dt, &objects);
}

void CPlayScene::Render()
{

	tileMap->Draw({ 0, 0 });

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->RenderBoundingBox(100);
		objects[i]->Render();
	}
	simon->Render();
	hud->Draw({ 0, 0 });
}

void CPlayScene::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->GetLockUpdate())
		return;
	if (simon->GetState() == SIMON_STATE_DIE)
		return;
	switch (KeyCode)
	{
	case DIK_Z:
		if (!simon->IsOnStair()
			&& simon->GetState() != SIMON_STATE_JUMP
			&& simon->GetState() != SIMON_STATE_ATTACK
			&& simon->GetState() != SIMON_STATE_ATTACK_SUBWEAPON)
			simon->StartJump();
		break;
	case DIK_X:
		if (game->IsKeyDown(DIK_UP))
			simon->StartAttackSub(&objects);
		else
			simon->StartAttack();
		break;
	case DIK_C:
		simon->StartAttackSub(&objects);
		break;
	case DIK_A:
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(40.0f, 375.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_S:
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(1433.0f, 280.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_D:
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(1905.0f, 375.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_UP:
		break;
	}
}

void CPlayScene::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_DOWN:
	case DIK_UP:
	case DIK_LEFT:
	case DIK_RIGHT:
		if (simon->IsOnStair())
			simon->SetSpeed(0, 0);
		break;
	default:
		break;
	}
}

void CPlayScene::KeyState(BYTE * states)
{
	if (simon->GetLockUpdate())
		return;
	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE)
		return;
	if (simon->GetAttackStart() > 0 || simon->GetJumpStart() > 0)
		return;

	// IDLE
	simon->SetState(SIMON_STATE_IDLE);

	// KEY STATE DOWN
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (simon->IsOnStair())
			simon->SetState(SIMON_STATE_DOWN_STAIR);
		else if (simon->GetColidingStair())
		{
			if (simon->GetColidingStair()->GetNy() < 0)
			{
				float x, y;
				simon->GetColidingStair()->GetPosition(x, y);
				simon->SetPosition(x, y);
				simon->SetState(SIMON_STATE_DOWN_STAIR);
			}
			else
				simon->SetState(SIMON_STATE_SIT);
		}
		else
			simon->SetState(SIMON_STATE_SIT);
	}
	// KEY STATE UP
	if (game->IsKeyDown(DIK_UP))
	{
		if (simon->IsOnStair())
			simon->SetState(SIMON_STATE_UP_STAIR);
		else if (simon->GetColidingStair())
			if (simon->GetColidingStair()->GetNy() > 0)
			{
				float x, y;
				simon->GetColidingStair()->GetPosition(x, y);
				simon->SetPosition(x, y);
				simon->SetState(SIMON_STATE_UP_STAIR);
			}
	}
	// KEY STATE RIGHT
	if (game->IsKeyDown(DIK_RIGHT))
		if (simon->IsOnStair())
			if (simon->GetCurrentStair()->GetNx() > 0)
				simon->SetState(SIMON_STATE_UP_STAIR);
			else
				simon->SetState(SIMON_STATE_DOWN_STAIR);
		else
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
	// KEY STATE LEFT
	if (game->IsKeyDown(DIK_LEFT))
		if (simon->IsOnStair())
			if (simon->GetCurrentStair()->GetNx() < 0)
				simon->SetState(SIMON_STATE_UP_STAIR);
			else
				simon->SetState(SIMON_STATE_DOWN_STAIR);
		else
			simon->SetState(SIMON_STATE_WALKING_LEFT);
}
