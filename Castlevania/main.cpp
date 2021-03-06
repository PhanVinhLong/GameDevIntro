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

#include "SceneManager.h"

using json = nlohmann::json;

LPGAME game;
CSceneManager* sceneManager;

LPDIRECT3DDEVICE9 d3ddv;
LPDIRECT3DSURFACE9 bb;
LPD3DXSPRITE spriteHandler;

class CSampleKeyHander : public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	sceneManager->GetCurrentScene()->OnKeyDown(KeyCode);
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	sceneManager->GetCurrentScene()->OnKeyUp(KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	sceneManager->GetCurrentScene()->KeyState(states);
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

void LoadResources()
{
	d3ddv = game->GetDirect3DDevice();
	bb = game->GetBackBuffer();
	spriteHandler = game->GetSpriteHandler();

	sceneManager = CSceneManager::GetInstance();
	sceneManager->LoadResource();
	sceneManager->ChangeScene(ID_SCENE_INTRO);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	sceneManager->Update(dt);
}

/*
	Render a frame
*/
void Render()
{
	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);

		sceneManager->Render();

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