#include "Scene.h"

int CScene::currentSceneId;

CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::OnKeyDown(int keyCode)
{
}

void CScene::OnKeyUp(int keyCode)
{
}

void CScene::KeyState(BYTE * states)
{
}

int CScene::GetId()
{
	return id;
}

int CScene::GetCurrentSceneId()
{
	return currentSceneId;
}

void CScene::SetCurrentSceneId(int id)
{
	currentSceneId = id;
}
