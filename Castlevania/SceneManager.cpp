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

// https://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
// covert std::string to std:: wstring
std::wstring s2ws4(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void CSceneManager::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	ifstream file("textures\\animation.json");
	json j = json::parse(file);

	// Load textures
	for (auto iter : j["texture"])
	{
		wstring sTmp;
		sTmp = s2ws4(iter[1]);
		LPCWSTR imagePath = sTmp.c_str();
		textures->Add(iter[0], imagePath, iter[2]);
	}

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
}

void CSceneManager::Update(DWORD dt)
{
	if (currentScene->GetId() != CScene::GetCurrentSceneId())
	{
		ChangeScene(CScene::GetCurrentSceneId());
		DebugOut(L"[INFO] Scene changed to: %d\n", CScene::GetCurrentSceneId());
	}
	currentScene->Update(dt);
}

void CSceneManager::Render()
{
	currentScene->Render();
}
