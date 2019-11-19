////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TiledMap
//
// Germán Martínez
//
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef ___TiledMap_h___
#define ___TiledMap_h___
#include <vector>

class Texture;
class Graphics;

class TiledMap
{
	int*				tiles;
	int					tilesLength;
	int					mapWidth;
	int					mapHeight;
	int					tileWidth;
	int					tileHeight;
public:
	TiledMap(const char* tmxName);
	~TiledMap();
public:
	void render(Graphics* gr, int dx, int dy);
private:
	void renderTile(Graphics* gr, int dx, int dy, int tileX, int tileY, int tileIndex);
};

#endif
