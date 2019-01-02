#pragma once
#include "Scene.h"
#include "IntroScene.h"
#include "PlayScene.h"

#define ID_SCENE_INTRO		0
#define ID_SCENE_PLAY		1
#define ID_SCENE_END		2

class CSceneManager
{
	CScene* currentScene;

	CSceneManager();
	static CSceneManager * __instance;
	static int currentSceneId;
public:
	~CSceneManager();

	CScene* GetCurrentScene();
	static CSceneManager* GetInstance();
	void ChangeScene(int sceneId);

	void LoadResource();
	void Update(DWORD dt);
	void Render();
};

