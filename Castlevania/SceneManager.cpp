#include "SceneManager.h"

CSceneManager * CSceneManager::__instance;

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

CScene * CSceneManager::GetCurrentScene()
{
	return currentScene;
}

CSceneManager * CSceneManager::GetInstance()
{
	if (__instance == NULL) __instance = new CSceneManager();
	return __instance;
}

void CSceneManager::ChangeScene(int sceneId)
{
	delete currentScene;
	switch (sceneId)
	{
	case ID_SCENE_INTRO:
		currentScene = new CIntroScene();
		break;
	case ID_SCENE_PLAY:
		currentScene = new CPlayScene();
		break;
	case ID_SCENE_END:
		break;
	default:
		break;
	}
}
