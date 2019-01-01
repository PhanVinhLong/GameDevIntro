#pragma once
#include <fstream>
#include "PlayScene.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Sprites.h"
#include "Textures.h"
#include "json.hpp"

#define ID_TEX_TITLE		0

using json = nlohmann::json;

class CIntroScene :
	public CScene
{
	LPANIMATION ani;
	LPANIMATION aniBG;
public:
	CIntroScene();
	~CIntroScene();

	void LoadResource();
	void Update(DWORD dt);
	void Render();

	void OnKeyDown(int KeyCode);
};

