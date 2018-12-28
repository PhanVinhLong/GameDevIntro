/* =================================================================||
||																	||
||	INTRODUCTION TO GAME PROGRAMMING SE102							||
||																	||
||	CASTLEVANIA														||
||																	||
||	PHAN VINH LONG - 16520695										||
||																	||
||================================================================= */

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

#include "TileMap.h"
#include "Viewport.h"
#include "HUD.h"
#include "Text.h"
#include "Candle.h"
#include "Panther.h"
#include "MapSet.h"
#include "PhantomBat.h"

using json = nlohmann::json;

LPGAME game;

CSimon* simon;

LPVIEWPORT viewport;
LPTILEMAP tileMap;
LPHUD hud;

vector<LPGAMEOBJECT> objects;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (simon->GetLockUpdate())
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
			simon->StartAttackSub();
		else
			simon->StartAttack();
		break;
	case DIK_C:
		simon->StartAttackSub();
		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(40.0f, 375.0f);
		simon->SetSpeed(0, 0);
		break;
	case DIK_S:
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(40.0f, 375.0f);
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

void CSampleKeyHander::OnKeyUp(int KeyCode)
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

void CSampleKeyHander::KeyState(BYTE *states)
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
				simon->SetState(SIMON_STATE_DOWN_STAIR);
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
				//float x, y;
				//simon->GetPosition(x, y);
				//simon->SetPosition(x, y - 2);
				simon->SetState(SIMON_STATE_UP_STAIR);
			}
	}
	// KEY STATE RIGHT
	if (game->IsKeyDown(DIK_RIGHT))
		if(simon->IsOnStair())
			if(simon->GetCurrentStair()->GetNx() > 0)
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

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	viewport = CViewport::GetInstance();

	CTextures * textures = CTextures::GetInstance();

	tileMap = new CTileMap();
	tileMap->LoadFromFile(L"textures\\map01.json");
	
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemy.png", D3DCOLOR_XRGB(96, 68, 106));
	textures->Add(ID_TEX_OBJECT, L"textures\\objects.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM, L"textures\\items.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HUD_BG, L"textures\\HUD.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_HEALTH, L"textures\\health.png", 0);
	textures->Add(ID_TEX_BOSS, L"textures\\boss.png", D3DCOLOR_XRGB(168, 40, 88));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	ifstream file("textures\\animation.json");
	json j = json::parse(file);

	// Load sprites
	for (auto iter : j["sprite"])
		sprites->Add(iter[0], iter[1], iter[2], iter[3], iter[4], iter[5], iter[6], { iter[7], iter[8] });

	// Load animation
	LPANIMATION ani;
	for (auto iter : j["animation"])
	{
		ani = new CAnimation(iter[1]);
		for (int i : iter[2]) ani->Add(i);
		animations->Add(iter[0], ani);
		DebugOut(L"Added animation %d\n", (int)iter[0]);
	}
	file.close();

	file.open("textures\\map01.json");
	j = json::parse(file);

	// Load objects
	simon = CSimon::GetInstance();
	simon->SetPosition(30.0f, 143.0f);
	objects.push_back(simon);

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
		else if (i["name"] == "boss")	// panther enemies
			for (auto iter : i["objects"])
			{
				CPhantomBat* phantomBat  = new CPhantomBat({ float(iter["x"]), float(iter["y"]) + iter["height"] });
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
	}

	// add a HUD_HEIGHT to objects's heigth
	for (auto iter : objects)
		iter->AddPosition(0, HUD_HEIGHT);

	hud = CHUD::GetInstance();
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	vector<LPGAMEOBJECT> coObjects;

	/*for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}*/

	for (auto iter : objects)
		iter->Update(dt, &objects);

	for (int i = 1; i < objects.size(); i++)
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
	viewport->Update(playerPos, simon->GetWidthMapStart()*16, simon->GetWidthMapEnd()*16);
	tileMap->Update(dt, &objects);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		tileMap->Draw({ 0, 0 });

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->RenderBoundingBox(100);
			objects[i]->Render();
		}
		simon->Render();
		hud->Draw({ 0, 0 });

		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}