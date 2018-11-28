#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include "Game.h"
#include "Textures.h"

#define ID_TEX_HUD_BG	50

class CHUD
{
private:
	LPDIRECT3DTEXTURE9 texBackground;
public:
	CHUD();
	~CHUD();

	void Draw(D3DXVECTOR2 position);
};

typedef CHUD* LPHUD;
