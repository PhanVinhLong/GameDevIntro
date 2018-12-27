#define _CRT_SECURE_NO_WARNINGS
#include "HUD.h"

CHUD* CHUD::__instance;

CHUD::CHUD()
{
	player = CSimon::GetInstance();
	this->texBackground = CTextures::GetInstance()->Get(ID_TEX_HUD_BG);
	this->texHealth = CTextures::GetInstance()->Get(ID_TEX_HEALTH);
	text = CText::GetInstance();
	for (int i = 0; i < 3; i++)
		listHealth.insert(pair<int, RECT>(i, { 5 * i, 0, 5 * (i + 1), 8 }));

	enemyHealth = 16;
}

void CHUD::DrawHealth(int id, D3DXVECTOR2 position)
{
	RECT sourceRect = listHealth[id];
	CGame::GetInstance()->Draw(position.x, position.y, texHealth, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom);
}

CHUD::~CHUD()
{
}

char* IntToChar(int value, int len = 10)
{
	char* c = new char[len + 1];
	c[len] = '\0';
	for (int i = len - 1; i >= 0; i--)
	{
		c[i] = value % 10 + 48;
		value = value / 10;
	}
	return c;
}

void CHUD::Draw(D3DXVECTOR2 position)
{
	CGame::GetInstance()->Draw(0, 0, texBackground, 0, 0, 256, 40);

	// scores
	text->DrawString("SCORE-", { 1,3 });
	text->DrawString(IntToChar(player->GetScore(), 6), { 49, 3 });

	// time
	text->DrawString("TIME", { 105,3 });
	text->DrawString("0300", { 141, 3 });

	// state
	text->DrawString("STAGE", { 181,3 });
	text->DrawString("01", { 225, 3 });

	// player's heart
	text->DrawString(IntToChar(player->GetHeart(), 2), { 205, 16 });

	// player's health
	text->DrawString("PLAYER", { 1,3 + 10 });
	for (int i = 0; i < SIMON_MAX_HEALTH; i++)
	{
		int tmpId = i < player->GetHealth() ? 0 : 1;
		DrawHealth(tmpId, { float(55 + i * 5), 13 });
	}

	// enemy's health
	text->DrawString("ENEMY", { 1,3 + 20 });
	for (int i = 0; i < 16; i++)
	{
		int tmpId = i < enemyHealth ? 2 : 1;
		DrawHealth(tmpId, { float(55 + i * 5), 24 });
	}

	// item
	GetItemSprite()->Draw(164, 29);

	// player's life
	text->DrawString(IntToChar(player->GetLife(), 2), { 205, 25 });
}

CHUD * CHUD::GetInstance()
{
	if (__instance == NULL) __instance = new CHUD();
	return __instance;
}

LPSPRITE CHUD::GetItemSprite()
{
	int spriteId;
	int itemId = player->GetSubWeaponID();

	switch (itemId)
	{
	case ID_SUBWEAPON_DAGGER:
		spriteId = 12003;
		break;
	case ID_SUBWEAPON_AXE:
		spriteId = 12011;
		break;
	case ID_SUBWEAPON_HOLY_WATER:
		spriteId = 12020;
		break;
	case ID_SUBWEAPON_BOOMERANG:
		spriteId = 0;
		break;
	case ID_SUBWEAPON_STOPWATCH:
		spriteId = 0;
		break;
	default:
		spriteId = 0;
		break;
	}
	return CSprites::GetInstance()->Get(spriteId);
}

void CHUD::SetEnemyHealth(int health)
{
	enemyHealth = health;
}
