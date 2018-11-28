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

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "Torch.h"
#include "LargeHeart.h"

#include "TileMap.h"
#include "Viewport.h"
#include "HUD.h"

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH	256
#define SCREEN_HEIGHT	50 + 16 * 14

#define MAX_FRAME_RATE	120

#define ID_TEX_SIMON	0
#define ID_TEX_ENEMY	10
#define ID_TEX_MISC		20
#define ID_TEX_OBJECT	30
#define ID_TEX_ITEM		40

CGame *game;

CSimon *simon;

CViewport *viewport;
CTileMap *tileMap;
CHUD* hud;

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
	switch (KeyCode)
	{
	case DIK_X:
		if (simon->GetState() != SIMON_STATE_JUMP && simon->GetState() != SIMON_STATE_ATTACK)
			simon->StartJump();
		break;
	case DIK_Z:
		simon->StartAttack();
		break;
	case DIK_C:
		simon->StartAttackSub();
		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetPosition(50.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	// disable control key when Mario die 
	if (simon->GetState() == SIMON_STATE_DIE)
		return;
	if (simon->GetAttackStart() > 0 || simon->GetJumpStart() > 0)
		return;

	if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else if (game->IsKeyDown(DIK_DOWN))
		simon->SetState(SIMON_STATE_SIT);
	else
		simon->SetState(SIMON_STATE_IDLE);
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
	
	textures->Add(ID_TEX_SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_OBJECT, L"textures\\objects.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM, L"textures\\items.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));


	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	
	sprites->Add(10001, 105, 8, 121, 39, texSimon, 1, { 0, 0 });		// simon idle right
	sprites->Add(10002, 105, 8, 121, 39, texSimon, 1, { 0, 0 });		// simon walk right
	sprites->Add(10003, 132, 8, 147, 39, texSimon, 1, { 0, 0 });
	sprites->Add(10004, 160, 8, 176, 39, texSimon, 1, { 0, 0 });
	sprites->Add(10005, 132, 8, 147, 39, texSimon, 1, { 0, 0 });

	sprites->Add(10011, 105, 8, 121, 39, texSimon);						// simon idle left
	sprites->Add(10012, 105, 8, 121, 39, texSimon);						// simon walk left
	sprites->Add(10013, 132, 8, 147, 39, texSimon);
	sprites->Add(10014, 160, 8, 176, 39, texSimon);
	sprites->Add(10015, 132, 8, 147, 39, texSimon);

	sprites->Add(10021, 100, 52, 130, 83, texSimon, 1, { -8, 0 });		// simon attack right
	sprites->Add(10022, 148, 52, 178, 83, texSimon, 1, { -8, 0 });
	sprites->Add(10023, 198, 52, 228, 83, texSimon, 1, { -8, 0 });

	sprites->Add(10031, 100, 52, 130, 83, texSimon, 0, { -6, 0 });		// simon attack left
	sprites->Add(10032, 148, 52, 178, 83, texSimon, 0, { -6, 0 });
	sprites->Add(10033, 198, 52, 228, 83, texSimon, 0, { -6, 0 });

	sprites->Add(10041, 187, 15, 204, 39, texSimon, 1, { 0, 0 });		// simon sit right

	sprites->Add(10051, 187, 15, 204, 39, texSimon, 0, { 0, 0 });		// simon sit left

	sprites->Add(10061, 350, 129, 375, 153, texSimon, 1, { 0, 0 });		// simon sit attack right
	sprites->Add(10062, 325, 120, 343, 154, texSimon, 1, { 0, 0 });
	sprites->Add(10063, 293, 130, 314, 153, texSimon, 1, { 0, 0 });

	sprites->Add(10071, 350, 129, 375, 153, texSimon, 0, { 0, 0 });		// simon sit attack left
	sprites->Add(10072, 325, 120, 343, 154, texSimon, 0, { 0, 0 });
	sprites->Add(10073, 293, 130, 314, 153, texSimon, 0, { 0, 0 });

	sprites->Add(10099, 215, 120, 231, 135, texSimon);					// simon die

	sprites->Add(10101, 83, 9, 91, 33, texSimon, 1, { -15, 0 });			// whip 0 right
	sprites->Add(10102, 59, 14, 74, 33, texSimon, 1, { -14, -7 });
	sprites->Add(10103, 27, 19, 52, 26, texSimon, 1, { 22, -17 });

	sprites->Add(10111, 83, 9, 91, 33, texSimon, 0, { 15 - -7, 0 });		// whip 0 left
	sprites->Add(10112, 59, 14, 74, 33, texSimon, 0, { 14 - -1, -7 });
	sprites->Add(10113, 27, 19, 52, 26, texSimon, 0, { -22 - 9, -17 });

	sprites->Add(10121, 82, 38, 91, 62, texSimon, 1, { -15, 0 });			// whip 1 right
	sprites->Add(10122, 62, 39, 77, 59, texSimon, 1, { -14, -7 });
	sprites->Add(10123, 32, 43, 56, 50, texSimon, 1, { 22, -17 });

	sprites->Add(10131, 82, 38, 91, 62, texSimon, 0, { 15 - -7, 0 });		// whip 1 left
	sprites->Add(10132, 62, 39, 77, 59, texSimon, 0, { 14 - -1, -7 });
	sprites->Add(10133, 32, 43, 56, 50, texSimon, 0, { -22 - 9, -17 });

	sprites->Add(10141, 83, 67, 92, 92, texSimon, 1, { -15, 0 });			// whip 2 right
	sprites->Add(10142, 58, 70, 74, 91, texSimon, 1, { -14, -7 });
	sprites->Add(10143, 12, 75, 55, 82, texSimon, 1, { 22, -17 });

	sprites->Add(10151, 83, 67, 92, 92, texSimon, 0, { 15 - -7, 0 });		// whip 2 left
	sprites->Add(10152, 58, 70, 74, 91, texSimon, 0, { 14 - -1, -7 });
	sprites->Add(10153, 12, 75, 55, 82, texSimon, 0, { -22 - 9, -17 });

	LPDIRECT3DTEXTURE9 texObjects = textures->Get(ID_TEX_OBJECT);

	sprites->Add(11001, 47, 25, 64, 56, texObjects, 0, { 0, 0 });		// torch
	sprites->Add(11002, 74, 23, 91, 56, texObjects, 0, { 0, 0 });

	LPDIRECT3DTEXTURE9 texItems = textures->Get(ID_TEX_ITEM);

	sprites->Add(12001, 123, 58, 136, 69, texItems, 0, { 0, 0 });		// large heart

	sprites->Add(12002, 43, 42, 61, 60, texItems, 0, { 0, 0 });			// whip upgrade

	sprites->Add(12003, 176, 39, 194, 49, texItems, 0, { 0, 0 });		// dagger right (item)
	sprites->Add(12004, 176, 39, 194, 49, texItems, 1, { 0, 0 });		// dagger left

	LPANIMATION ani;

	ani = new CAnimation(100);		// idle right
	ani->Add(10001);
	animations->Add(100, ani);

	ani = new CAnimation(100);		// idle left
	ani->Add(10011);
	animations->Add(101, ani);

	ani = new CAnimation(100);		// walk right
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	ani->Add(10005);
	animations->Add(102, ani);

	ani = new CAnimation(100);		// walk left
	ani->Add(10012);
	ani->Add(10013);
	ani->Add(10014);
	ani->Add(10015);
	animations->Add(103, ani);

	ani = new CAnimation(100);		// simon attack right
	ani->Add(10021);
	ani->Add(10022);
	ani->Add(10023);
	animations->Add(104, ani);

	ani = new CAnimation(100);		// simon attack left
	ani->Add(10031);
	ani->Add(10032);
	ani->Add(10033);
	animations->Add(105, ani);

	ani = new CAnimation(100);		// simon sit right
	ani->Add(10041);
	animations->Add(106, ani);

	ani = new CAnimation(100);		// simon sit left
	ani->Add(10051);
	animations->Add(107, ani);

	ani = new CAnimation(100);		// simon sit attack right
	ani->Add(10061);
	ani->Add(10062);
	ani->Add(10063);
	animations->Add(108, ani);

	ani = new CAnimation(100);		// simon sit attack left
	ani->Add(10071);
	ani->Add(10072);
	ani->Add(10073);
	animations->Add(109, ani);

	ani = new CAnimation(100);		// simon die
	ani->Add(10099);
	animations->Add(110, ani);

	ani = new CAnimation(100);		// whip 0 right
	ani->Add(10101);
	ani->Add(10102);
	ani->Add(10103);
	animations->Add(111, ani);

	ani = new CAnimation(100);		// whip 0 left
	ani->Add(10111);
	ani->Add(10112);
	ani->Add(10113);
	animations->Add(112, ani);

	ani = new CAnimation(100);		// whip 1 right
	ani->Add(10121);
	ani->Add(10122);
	ani->Add(10123);
	animations->Add(113, ani);

	ani = new CAnimation(100);		// whip 1 left
	ani->Add(10131);
	ani->Add(10132);
	ani->Add(10133);
	animations->Add(114, ani);

	ani = new CAnimation(100);		// whip 2 right
	ani->Add(10141);
	ani->Add(10142);
	ani->Add(10143);
	animations->Add(115, ani);

	ani = new CAnimation(100);		// whip 2 left
	ani->Add(10151);
	ani->Add(10152);
	ani->Add(10153);
	animations->Add(116, ani);

	ani = new CAnimation(100);		// torch
	ani->Add(11001);
	ani->Add(11002);
	animations->Add(200, ani);

	ani = new CAnimation(100);		// large heart
	ani->Add(12001);
	animations->Add(300, ani);

	ani = new CAnimation(100);		// whip upgrade
	ani->Add(12002);
	animations->Add(301, ani);

	ani = new CAnimation(100);		// dagger right (item)
	ani->Add(12003);
	animations->Add(302, ani);

	ani = new CAnimation(100);		// dagger left
	ani->Add(12004);
	animations->Add(303, ani);

	simon = new CSimon();
	simon->AddAnimation(100);		// idle right			0
	simon->AddAnimation(101);		// idle left			1
	simon->AddAnimation(102);		// walk right			2
	simon->AddAnimation(103);		// walk left			3
	simon->AddAnimation(104);		// attack right			4
	simon->AddAnimation(105);		// attack left			5
	simon->AddAnimation(106);		// sit right			6
	simon->AddAnimation(107);		// sit left				7
	simon->AddAnimation(108);		// sit attack right		8
	simon->AddAnimation(109);		// sit attack left		9
	simon->AddAnimation(110);		// die					10
	simon->SetPosition(30.0f, 143.0f);
	objects.push_back(simon);

	for (int i = 0; i < 50; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(-16 + i * 16.0f, 146);
		objects.push_back(brick);
	}
	for (int i = 0; i < 10; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(-16, 0 + i * 16.0f);
		objects.push_back(brick);
	}
	for (int i = 0; i < 10; i++)
	{
		CBrick *brick = new CBrick();
		brick->AddAnimation(601);
		brick->SetPosition(752, 0 + i * 16.0f);
		objects.push_back(brick);
	}

	CTorch* torch;
	torch = new CTorch({ 90 + 0 * 127.0f, 144.0f }, ID_LARGE_HEART);
	objects.push_back(torch);
	torch = new CTorch({ 90 + 1 * 127.0f, 144.0f }, ID_WHIP_UPGRADE);
	objects.push_back(torch);
	torch = new CTorch({ 90 + 3 * 127.0f, 144.0f }, ID_LARGE_HEART);
	objects.push_back(torch);
	torch = new CTorch({ 90 + 4 * 127.0f, 144.0f }, ID_DAGGER_ITEM);
	objects.push_back(torch);
	torch = new CTorch({ 90 + 2 * 127.0f, 144.0f }, ID_WHIP_UPGRADE);
	objects.push_back(torch);

	for (auto iter : objects)
		iter->AddPosition(0, HUD_HEIGHT);

	hud = new CHUD();
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
	viewport->Update(playerPos, tileMap->GetWidthStart(playerPos.y), tileMap->GetWidthEnd(playerPos.y));
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