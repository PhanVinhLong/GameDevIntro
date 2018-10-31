#pragma once
#include <unordered_map>
#include <d3dx9.h>

using namespace std;

/*
	Manage texture database
*/
class CTextures
{
private:
	static CTextures * __instance;

	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

	CTextures();

public:
	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 Get(unsigned int i);

	static CTextures * GetInstance();
};

class Textures
{
public:
	Textures();
	~Textures();
};
