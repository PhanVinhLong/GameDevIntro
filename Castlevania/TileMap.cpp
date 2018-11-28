#include "TileMap.h"
#include "define.h"

std::wstring s2ws(const std::string& s);

CTileSet::CTileSet()
{
}

void CTileSet::LoadFromFile(LPCWSTR filePath)
{
	// Load info
	ifstream file(filePath);
	json j = json::parse(file);

	tileWidth = j["tilesets"][0]["tilewidth"].get<int>();
	tileHeight = j["tilesets"][0]["tileheight"].get<int>();
	numOfColumn = j["tilesets"][0]["columns"].get<int>();
	int tileCount = j["tilesets"][0]["tilecount"].get<int>();
	string tmpPath = "textures\\" + j["/tilesets/0/image"_json_pointer].get<string>();

	numOfRow = (tileCount - 1) / numOfColumn + 1;
		
	wstring sTmp;
	sTmp = s2ws(tmpPath);
	LPCWSTR imagePath = sTmp.c_str();

	/*int tileWidth = 16;
	int tileHeight = 16;
	int numOfColumn = 11;
	int tileCount = 165;
	int numOfRow = 15;
	LPCWSTR imagePath = L"textures\\mapFile_bank.png";*/
	
	// Add list tiles
	for(int i = 0; i < numOfRow; i++)
		for (int j = 0; j < numOfColumn; j++)
		{
			RECT tmpRect = { j * tileWidth, i * tileHeight, (j + 1) * tileWidth, (i + 1) * tileHeight };
			int tmpID = i * numOfColumn + j + 1;
			listTile.insert(pair<int, RECT>(tmpID, tmpRect));
		}

	// Add texture
	CTextures::GetInstance()->Add(ID_TEX_TILESET_01, imagePath, 0);
	this->texture = CTextures::GetInstance()->Get(ID_TEX_TILESET_01);
	if (texture)
		DebugOut(L"Load tile texure OK: %s", imagePath);

	file.close();
}

void CTileSet::DrawTile(int id, D3DXVECTOR2 position)
{
	RECT sourceRect = listTile[id];
	CGame::GetInstance()->Draw(position.x, position.y, texture, sourceRect.left, sourceRect.top, sourceRect.right, sourceRect.bottom);
}

int CTileSet::GetTileWidth()
{
	return tileWidth;
}

int CTileSet::GetTileHeight()
{
	return tileHeight;
}

// https://stackoverflow.com/questions/27220/how-to-convert-stdstring-to-lpcwstr-in-c-unicode
// covert std::string to std:: wstring
std::wstring s2ws(const std::string& s)
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

CTileMap::CTileMap()
{
	
	tileSet = new CTileSet();
}

void CTileMap::LoadFromFile(LPCWSTR filePath)
{
	// Load info
	ifstream file(filePath);
	json j = json::parse(file);

	tileRow = j["/layers/0/height"_json_pointer].get<int>();
	tileColumn = j["/layers/0/width"_json_pointer].get<int>();
	widthEdge = j["/layers/0/edge"_json_pointer].get<vector<vector<int>>>();

	vector<int> data = j["/layers/0/data"_json_pointer].get<vector<int>>();

	// Map data from vector to matrix
	mapData = new int*[tileRow];
	for (int i = 0; i < tileRow; i++)
	{
		mapData[i] = new int[tileColumn];
		for (int j = 0; j < tileColumn; j++)
		{
			int tmp = i * tileColumn + j;
			mapData[i][j] = data[tmp];
		}
	}

	// Load tileset
	tileSet->LoadFromFile(filePath);
}

void CTileMap::Draw(D3DXVECTOR2 position)
{
	CViewport * viewport = CViewport::GetInstance();

	int wStart = viewport->GetPosition().x / tileSet->GetTileWidth();
	int hStart = viewport->GetPosition().y / tileSet->GetTileHeight();
	int wEnd = wStart + viewport->GetWidth() / tileSet->GetTileWidth();
	int hEnd = hStart + viewport->GetHeight() / tileSet->GetTileHeight();

	for (int i = hStart; i < hEnd; i++)
	{
		for (int j = wStart; j < wEnd; j++)
		{
			D3DXVECTOR2 pos;
			pos.x = position.x + j * tileSet->GetTileWidth();
			pos.y = position.y + i * tileSet->GetTileHeight() + HUD_HEIGHT;
			pos = CViewport::GetInstance()->WorldToViewportPos(pos);
			tileSet->DrawTile(mapData[i][j], pos);
		}
	}
}

int CTileMap::GetWidthStart(int playerPosY)
{
	return widthEdge[(playerPosY-HUD_HEIGHT) / 176][0] * tileSet->GetTileWidth();
}

int CTileMap::GetWidthEnd(int playerPosX)
{
	return widthEdge[(playerPosX - 40) / 176][1] * tileSet->GetTileWidth();
}
