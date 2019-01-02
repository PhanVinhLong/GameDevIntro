#include "IntroScene.h"

CIntroScene::CIntroScene()
{
	id = ID_SCENE_INTRO;
	SetCurrentSceneId(ID_SCENE_INTRO);
	LoadResource();
}

CIntroScene::~CIntroScene()
{
}

void CIntroScene::LoadResource()
{
	CAnimations * animations = CAnimations::GetInstance();

	ani = animations->Get(ID_ANI_INTRO_ANI);
	aniBG = animations->Get(ID_ANI_INTRO_BG);
}

void CIntroScene::Update(DWORD dt)
{
}

void CIntroScene::Render()
{
	aniBG->Render(2, 226);
	ani->Render(185, 155);
}

void CIntroScene::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_RETURN:
		CScene::SetCurrentSceneId(ID_SCENE_PLAY);
		break;
	default:
		break;
	}
}
