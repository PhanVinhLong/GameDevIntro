#include "IntroScene.h"

CIntroScene::CIntroScene()
{
	id = ID_SCENE_INTRO;
	LoadResource();
}

CIntroScene::~CIntroScene()
{
}

void CIntroScene::LoadResource()
{
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_TITLE, L"textures\\title.png", D3DCOLOR_ARGB(255,5,5,5));
	sprites->Add(0, 2, 2, 258, 226, 0, 0, { 0, 0 });

	sprites->Add(1, 275, 2, 347, 58, 0, 0, { 0, 0 });
	sprites->Add(2, 353, 2, 425, 58, 0, 0, { 0, 0 });
	sprites->Add(3, 431, 2, 503, 58, 0, 0, { 0, 0 });
	sprites->Add(4, 511, 2, 581, 58, 0, 0, { 0, 0 });
	sprites->Add(5, 589, 2, 659, 58, 0, 0, { 0, 0 });

	sprites->Add(6, 275, 63, 347, 119, 0, 0, { 0, 0 });
	sprites->Add(7, 353, 63, 425, 119, 0, 0, { 0, 0 });
	sprites->Add(8, 431, 63, 503, 119, 0, 0, { 0, 0 });
	sprites->Add(9, 511, 63, 581, 119, 0, 0, { 0, 0 });
	sprites->Add(10, 589, 63, 659, 119, 0, 0, { 0, 0 });

	sprites->Add(11, 275, 125, 347, 181, 0, 0, { 0, 0 });
	sprites->Add(12, 353, 125, 425, 181, 0, 0, { 0, 0 });
	sprites->Add(13, 431, 125, 503, 181, 0, 0, { 0, 0 });
	sprites->Add(14, 511, 125, 583, 181, 0, 0, { 0, 0 });
	sprites->Add(15, 589, 125, 661, 181, 0, 0, { 0, 0 });

	ani = new CAnimation(100);
	for (int i = 12; i <= 15; i++) ani->Add(i);

	aniBG = new CAnimation(100);
	aniBG->Add(0);
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
		CSceneManager::GetInstance()->ChangeScene(ID_SCENE_PLAY);
		break;
	default:
		break;
	}
}
