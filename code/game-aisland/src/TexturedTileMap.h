////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TexturedTileMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TexturedTileMap_h___
#define ___TexturedTileMap_h___

class Texture;
class Graphics;

class TexturedTileMap
{
	enum
	{
		TILE_SIZE = 16,
	};
	unsigned short*	tiles;
	Texture*		tileset;
	int				mapWidth;
	int				mapHeight;
	int				tilesCount;
public:
	TexturedTileMap(int w, int h, const char* tilesFilename, const char* tilesetFilename);
	~TexturedTileMap();
public:
	void render(Graphics* gr, int cameraX, int cameraY);
};

#endif
